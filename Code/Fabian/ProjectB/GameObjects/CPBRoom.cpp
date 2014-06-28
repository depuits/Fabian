#include "CPBRoom.h"

#include <Fabian.h>

#include <IContentManager.h>
#include <IRenderer.h>
#include <IShader.h>
#include <IMaterial.h>
#include <IMesh.h>

#include <vector>


//-------------------------------------
// Constructor
// p1 in* - int, the priorety of the service
//            ( the lower the higher the priorety )
CPBRoom::CPBRoom()
	:CPBGameObject()
	,m_pMesh(nullptr)
	,m_pMaterial(nullptr)
{
}
//-------------------------------------
// Destructor
CPBRoom::~CPBRoom()
{
}
//-------------------------------------
	
void CPBRoom::LoadData(IContentManager* pContent, IRenderer* pRenderer)	// used to load all the needed data for the object
{
	IShader *pShader = pContent->LoadShader("Shaders/SimpleShader");
	pShader->Apply();
	pShader->SetVarVec3(  pShader->GetVarId("LightPosition_worldspace"),    glm::vec3(100, 100, 100));
	pShader->SetVarF1(    pShader->GetVarId("LightPower"),                  1.0f);
	pShader->SetVarVec4(  pShader->GetVarId("LightColor"),                  glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	IImage  *pImage = pContent->LoadImage("Textures/FloorDif.png");

	m_pMaterial = Fab_MatCreateDifTexture(pShader, pImage);

	//! @todo create room mesh data
	//!    floor, walls, 'roof' and items
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	
	vertices.push_back( 0 ); vertices.push_back( 0 ); vertices.push_back( 0 );	// x, y, z
	vertices.push_back( 0 ); vertices.push_back( 1 ); vertices.push_back( 0 );	// normal
	vertices.push_back( 0 ); vertices.push_back( 0 );							// uv

	vertices.push_back( 1 ); vertices.push_back( 0 ); vertices.push_back( 0 );	// x, y, z
	vertices.push_back( 0 ); vertices.push_back( 1 ); vertices.push_back( 0 );	// normal
	vertices.push_back( 1 ); vertices.push_back( 0 );							// uv
	
	vertices.push_back( 1 ); vertices.push_back( 0 ); vertices.push_back( 1 );	// x, y, z
	vertices.push_back( 0 ); vertices.push_back( 1 ); vertices.push_back( 0 );	// normal
	vertices.push_back( 1 ); vertices.push_back( 1 );							// uv
	
	vertices.push_back( 0 ); vertices.push_back( 0 ); vertices.push_back( 1 );	// x, y, z
	vertices.push_back( 0 ); vertices.push_back( 1 ); vertices.push_back( 0 );	// normal
	vertices.push_back( 0 ); vertices.push_back( 1 );							// uv
	
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(0);

	indices.push_back(3);
	indices.push_back(2);
	indices.push_back(0);

	MeshData md;
	md.iCount = indices.size();
	md.iData = indices.data();
	md.vCount = vertices.size();
	md.vData = vertices.data();

	m_pMesh = pRenderer->LoadMesh(&md);//  pContent->LoadMesh("Meshes/Player.obj");
}
void CPBRoom::Init()						// used for (re)initializing the object
{
	//! @todo position room
}
void CPBRoom::Update(float dTime)				// called +-*when the onject needs to update
{
}
void CPBRoom::Draw()						// called when the object needs to be drawn
{
	m_pMaterial->Apply( m_Transform );
	m_pMesh->Draw();
}

