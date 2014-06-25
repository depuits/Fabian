#include "CPBPlayer.h"

#include <Fabian.h>

#include <IContentManager.h>
#include <IShader.h>
#include <IMaterial.h>
#include <IMesh.h>

#include <IInput.h>


//-------------------------------------
// Constructor
// p1 in* - int, the priorety of the service
//            ( the lower the higher the priorety )
CPBPlayer::CPBPlayer(IInput* pInput)
	:CPBGameObject()
	,m_pInput(pInput)
	,m_pMesh(nullptr)
	,m_pMaterial(nullptr)
{
}
//-------------------------------------
// Destructor
CPBPlayer::~CPBPlayer()
{
}
//-------------------------------------
	
void CPBPlayer::LoadData(IContentManager* pContent)	// used to load all the needed data for the object
{
	IShader *pShader = pContent->LoadShader("Shaders/SimpleShader");
	pShader->Apply();
	pShader->SetVarVec3(  pShader->GetVarId("LightPosition_worldspace"),    glm::vec3(0, 100, 0));
	pShader->SetVarF1(    pShader->GetVarId("LightPower"),                  1.0f);
	pShader->SetVarVec4(  pShader->GetVarId("LightColor"),                  glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	IImage  *pImage = pContent->LoadImage("Textures/PlayerDif.png");

	m_pMaterial = Fab_MatCreateDifTexture(pShader, pImage);
	m_pMesh = pContent->LoadMesh("Meshes/Player.obj");
}
void CPBPlayer::Init()						// used for (re)initializing the object
{
}
void CPBPlayer::Update(float dTime)				// called when the onject needs to update
{
	//! @todo change to fluid control

	float speed = 50.0f;
	glm::vec3 dpos;
	
	if( m_pInput->GetKeyState( FKEY_UP ) & DOWN )
	{
		dpos.z += 1;
	}
	if( m_pInput->GetKeyState( FKEY_DOWN ) & DOWN )
	{
		dpos.z -= 1;
	}

	if( m_pInput->GetKeyState( FKEY_LEFT ) & DOWN )
	{
		dpos.x += 1;
	}
	if( m_pInput->GetKeyState( FKEY_RIGHT ) & DOWN )
	{
		dpos.x -= 1;
	}
	
	dpos *= dTime * speed;
	m_Transform.Move(dpos);
}
void CPBPlayer::Draw()						// called when the object needs to be drawn
{
	m_pMaterial->Apply( m_Transform );
	m_pMesh->Draw();
}

