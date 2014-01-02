#include "CServiceGame.h"

#include "CKernel.h"

#include "IInput.h"
#include "IRenderer.h"
#include "CContentManager.h"

#include "IShader.h"
#include "CMatDifTexture.h"
#include "IImage.h"

#include "CCompModel.h"
#include "CCompCamera.h"
#include "CCompControl.h"

#include "CGameObject.h"

#include "CGlobalAccessor.h"

#include "CLog.h"

#include "Game/Grid.h"

#include "Game/Entity.h"
#include "Game/Player.h"
#include "Game/Enemy1D.h"
#include "Game/EnemyRot.h"

#include "Game/Floor.h"
#include "Game/Wall.h"
#include "Game/Bomb.h"
#include "Game/Candy.h"
#include "Game/Exit.h"
#include "Game/Water.h"
#include "Game/MovingFloor.h"
#include "Game/CollapseFloor.h"

#include <iostream>
#include <fstream>

std::vector<CGameObject*> g_vpGameObjects;

IMaterial   *g_pMatDefault,
            *g_pMatGround,
            *g_pMatWater;

//******************************************
// Class CServiceGame:
// game specific service which defines the actual game
//******************************************
float CServiceGame::s_fDtime = 0;

//-------------------------------------
// Constructor
// p1 in* - int, the priorety of the service
//            ( the lower the higher the priorety )
CServiceGame::CServiceGame(int priorety)
	:IService(priorety)

	,m_pInput(nullptr)
	,m_pRenderer(nullptr)
	,m_pContent(nullptr)
{
}
//-------------------------------------
// Destructor
CServiceGame::~CServiceGame()
{
}
//-------------------------------------

//-------------------------------------
// !!! temp !!!
// gloabal helper class to send SMsg's
void SendMsg(int id, IService *pServ)
{
	SMsgRequest msg(id, pServ);
	CKernel::Get().SendMessage(&msg);
}
//-------------------------------------

//-------------------------------------
// Called when the service is registered in the kernel
// rv - return true on succes,
//         when false is returned then the service gets deleted
bool CServiceGame::Start()
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Game Service: Starting" );
	SendMsg(SM_INPUT, this);
	SendMsg(SM_RENDERER, this);

	SMsgTimer msg(TimerCallback);
	CKernel::Get().SendMessage(&msg);

	// just quit when the renderer or input wasn't filled in
	FASSERTR(m_pInput != nullptr);
	FASSERTR(m_pRenderer != nullptr);

	m_pRenderer->SetVSync(true);

	// make needed object accesable for user
	CGlobalAccessor::Get().AddObject("Input", m_pInput);

	IShader *pShader = m_pRenderer->LoadShader("Shaders/SimpleShader");
	pShader->Apply();
	pShader->SetVarVec3(  pShader->GetVarId("LightPosition_worldspace"),    glm::vec3(0, 100, 0));
	pShader->SetVarF1(    pShader->GetVarId("LightPower"),                  1.0f);
	pShader->SetVarVec4(  pShader->GetVarId("LightColor"),                  glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	m_pContent = new CContentManager(m_pRenderer);
	IImage  *pImage1 = m_pContent->LoadImage("Textures/uv.jpg"),
            *pImage2 = m_pContent->LoadImage("Textures/img_cheryl.jpg"),
            *pImage3 = m_pContent->LoadImage("Textures/CarDiffuseMap.png");

    g_pMatDefault = new CMatDifTexture(pShader, pImage3);
    g_pMatGround = new CMatDifTexture(pShader, pImage2);
    g_pMatWater = new CMatDifTexture(pShader, pImage1);

	CGameObject *pGo = new CGameObject();
	pGo->Init();
	CCompCamera* pCam = new CCompCamera();
	pGo->AddComponent( pCam );
	pGo->Transform()->SetPos( glm::vec3(0, 10 * Grid::SCALE, 0) );
	pGo->Transform()->SetRot( glm::vec3(0, 0, glm::half_pi<float>()) );
	pGo->Transform()->Rotate( glm::vec3(0, -glm::half_pi<float>(), 0));
	g_vpGameObjects.push_back(pGo);
	CGlobalAccessor::Get().AddObject("Camera", pGo);
	m_pRenderer->SetActiveCamera(pCam);

	LoadLevel();

	for (CGameObject* go : g_vpGameObjects)
		go->Init();

	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Game Service: Started" );
	return true;
}

void CServiceGame::LoadLevel()
{
	std::string file("level.lvl");

	int w = 0,
		h = 1; // start at 1 because last line doesn't need an \n
	int tw = 0;

	//read file twice
	// 1. read and count the grid size
	std::ifstream is(file);		// open file
	while (is.good())				// loop while extraction from file is possible
	{
		char c = (char)is.get();       // get character from file
		if (is.good())
		{
			// check which character i have
			std::cout << c;
			if ( c != '\n' )
				++tw;
			else
			{
				if( w < tw )
					w = tw;
				tw = 0;
				++h;
			}
		}
	}

	std::cout << "\n\nw: " << w << " - h: " << h << "\n";

	// return to start of the file and read again
	is.clear();
	is.seekg(0, std::ios::beg);

	// 2. read and load in objects
	Grid *pGrid = new Grid(w, h);
	CGlobalAccessor::Get().AddObject("Grid", pGrid);

    glm::vec2 vPos(0, 0);

	while (is.good())				// loop while extraction from file is possible
	{
		char c = (char)is.get();       // get character from file
		if (is.good())
		{
			// check which character i have
			switch(c)
			{
			case 'g':
				AddGridEntity(pGrid, vPos, new Floor(), new CCompModel( m_pContent->LoadMesh("Meshes/floor.obj"),  g_pMatGround ) );
				break;
			case 'm':
				AddGridEntity(pGrid, vPos, new MovingFloor(), new CCompModel( m_pContent->LoadMesh("Meshes/floor.obj"),  g_pMatDefault ) );
				break;
			case 'v':
				AddGridEntity(pGrid, vPos, new CollapseFloor(1), new CCompModel( m_pContent->LoadMesh("Meshes/floor.obj"),  g_pMatDefault ) );
				break;
			case '~':
				AddGridEntity(pGrid, vPos, new Water(), new CCompModel( m_pContent->LoadMesh("Meshes/floor.obj"),  g_pMatWater ) );
				break;
			case 'w':
				AddGridEntity(pGrid, vPos, new Wall(), new CCompModel( m_pContent->LoadMesh("Meshes/wall.obj"),  g_pMatDefault ) );
				break;
			case 'e':
				AddGridEntity(pGrid, vPos, new Exit(), new CCompModel( m_pContent->LoadMesh("Meshes/floor.obj"),  g_pMatDefault ) );
				break;
			case 'b':
				AddGridEntity(pGrid, vPos, new Bomb(), new CCompModel( m_pContent->LoadMesh("Meshes/floor.obj"),  g_pMatDefault ) );
				break;
			case 'c':
			{
				CGameObject *pGO = AddGridEntity(pGrid, vPos, new Candy(), new CCompModel( m_pContent->LoadMesh("Meshes/candy.obj"),  g_pMatDefault ) );
				pGO->AddComponent(new CCompModel( m_pContent->LoadMesh("Meshes/floor.obj"),  g_pMatGround ));
				break;
            }
			case 'p':
				{
					// first add a floor
					AddGridEntity(pGrid, vPos, new Floor(), new CCompModel( m_pContent->LoadMesh("Meshes/floor.obj"),  g_pMatGround ) );

					//then add player
					CGameObject *pGo = new CGameObject();
					Entity *pEnt = new Player();
					pEnt->SetRespawn(vPos);
					pEnt->SetGridPos(vPos);

					pGo->AddComponent( pEnt );
					pGo->AddComponent( new CCompModel( m_pContent->LoadMesh("Meshes/car.obj"),  g_pMatDefault ) );
					pGo->Transform()->SetScale( 0.5f );
					g_vpGameObjects.push_back(pGo);
					CGlobalAccessor::Get().AddObject("Player", pEnt);
					break;
				}

				// 1D enemys
			case '2':
			case '4':
			case '6':
			case '8':
				{
					glm::vec2 dir;
					switch(c)
					{
					case '2':
						dir = glm::vec2(0, 1);
						break;
					case '4':
						dir = glm::vec2(-1, 0);
						break;
					case '6':
						dir = glm::vec2(1, 0);
						break;
					case '8':
						dir = glm::vec2(0, -1);
						break;
					}

					// first add a floor
					AddGridEntity(pGrid, vPos, new Floor(), new CCompModel( m_pContent->LoadMesh("Meshes/floor.obj"),  g_pMatGround ) );

					//then add enemy
					CGameObject *pGo = new CGameObject();
					Entity *pEnt = new Enemy1D(dir);
					pEnt->SetRespawn(vPos);
					pEnt->SetGridPos(vPos);

					pGo->AddComponent( pEnt );
					pGo->AddComponent( new CCompModel( m_pContent->LoadMesh("Meshes/car.obj"),  g_pMatDefault ) );
					pGo->Transform()->SetScale( 0.5f );
					g_vpGameObjects.push_back(pGo);
					break;
				}

				// Rot enemys
				// CW
			case 's':
			case 'q':
			case 'd':
			case 'z':

			case 'k':
			case 'j':
			case 'l':
			case 'i':
				{
					glm::vec2 dir;
					char rotDir = 0;
					switch(c)
					{
					case 's':
						dir = glm::vec2(0, 1);
						rotDir = EnemyRot::CW;
						break;
					case 'q':
						dir = glm::vec2(-1, 0);
						rotDir = EnemyRot::CW;
						break;
					case 'd':
						dir = glm::vec2(1, 0);
						rotDir = EnemyRot::CW;
						break;
					case 'z':
						dir = glm::vec2(0, -1);
						rotDir = EnemyRot::CW;
						break;

					case 'k':
						dir = glm::vec2(0, 1);
						rotDir = EnemyRot::CCW;
						break;
					case 'j':
						dir = glm::vec2(-1, 0);
						rotDir = EnemyRot::CCW;
						break;
					case 'l':
						dir = glm::vec2(1, 0);
						rotDir = EnemyRot::CCW;
						break;
					case 'i':
						dir = glm::vec2(0, -1);
						rotDir = EnemyRot::CCW;
						break;
					}

					// first add a floor
					AddGridEntity(pGrid, vPos, new Floor(), new CCompModel( m_pContent->LoadMesh("Meshes/floor.obj"),  g_pMatGround ) );

					//then add enemy
					CGameObject *pGo = new CGameObject();
					Entity *pEnt = new EnemyRot(dir, rotDir);
					pEnt->SetRespawn(vPos);
					pEnt->SetGridPos(vPos);

					pGo->AddComponent( pEnt );
					pGo->AddComponent( new CCompModel( m_pContent->LoadMesh("Meshes/car.obj"),  g_pMatDefault ) );
					pGo->Transform()->SetScale( 0.5f );
					g_vpGameObjects.push_back(pGo);
					break;
				}
			}

			//progress when filled
			if ( c != '\n' )
				++vPos.x;
			else
			{
				vPos.x = 0;
				++vPos.y;
			}
		}
	}

	is.close();                // close file
}
CGameObject *CServiceGame::AddGridEntity(Grid* pGrid, glm::vec2& pos, GridEntity* pGEnt, IComponent* pComp)
{
	CGameObject *pGo = new CGameObject();
	pGo->AddComponent( pComp );
	pGo->AddComponent( pGEnt );
	pGo->Transform()->SetPos( glm::vec3(pos.x * Grid::SCALE, 0, pos.y * Grid::SCALE) );
	pGo->Transform()->SetScale( Grid::SCALE / 2 );
	g_vpGameObjects.push_back(pGo);

	pGrid->SetGObject((int)pos.x, (int)pos.y, pGEnt);

	return pGo;
}
//-------------------------------------
// Called every time the service has to update
void CServiceGame::Update()
{
	// update
	for (CGameObject* go : g_vpGameObjects)
		go->Update(s_fDtime);

	//draw
	m_pRenderer->Clear(0.01f, 0.1f, 0.4f, 1.0f);
	m_pRenderer->StartDraw();
	for (CGameObject* go : g_vpGameObjects)
		go->Draw();
    m_pRenderer->EndDraw();
}
//-------------------------------------
// Called when the service will be deleted
void CServiceGame::Stop()
{
	CLog::Get().Write(FLOG_LVL_INFO, FLOG_ID_APP, "Game Service: Stopping" );
	// we don't delete the mesh and image because it was loaded by de contentloader and it will destroy it for use

	for (CGameObject* go : g_vpGameObjects)
		delete go;
	g_vpGameObjects.clear();

	delete static_cast<Grid*>( CGlobalAccessor::Get().GetObject("Grid") );
	delete m_pContent;

	delete g_pMatDefault;
    delete g_pMatGround;
    delete g_pMatWater;
}
//-------------------------------------

//-------------------------------------
// Called when there are messages send somewhere
// p1 in - pointer to SMsg object
void CServiceGame::MsgProc(SMsg* sm)
{
	switch( sm->id )
	{
	case SM_INPUT + SM_H_RECEIVE:
		m_pInput = SMsg::Cast<SMsgInput*>(sm)->pInput;
		break;
	case SM_RENDERER + SM_H_RECEIVE:
		m_pRenderer = SMsg::Cast<SMsgRenderer*>(sm)->pRenderer;
		break;

	case SM_INPUT + SM_H_REMOVE:
	case SM_RENDERER + SM_H_REMOVE:
		CLog::Get().Write(FLOG_LVL_WARNING, FLOG_ID_APP, "Game Service: Stopping (Renderer or Input removed)" );
		this->SetCanKill(true);
		break;
	}
}
//-------------------------------------

//-------------------------------------
// Function used for timer callback
// p1 in - float, delta time
void CServiceGame::TimerCallback(float fDt)
{
	//if( fDt > 0.000000001f )
		s_fDtime = fDt;
		//__debugbreak();

}
//-------------------------------------


