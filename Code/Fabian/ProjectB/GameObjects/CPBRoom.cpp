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
	,m_pMeshFloor(nullptr)
	,m_pMeshWalls(nullptr)
	,m_pMeshRoof(nullptr)
	,m_pMaterialFloor(nullptr)
	,m_pMaterialWalls(nullptr)
	,m_pMaterialRoof(nullptr)
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
	m_pMaterialFloor = Fab_MatCreateDifTexture(pShader, pImage);

	pImage = pContent->LoadImage("Textures/WallDif.png");
	m_pMaterialWalls = Fab_MatCreateDifTexture(pShader, pImage);

	glm::vec2 size(15, 15);
	float height = 2.0f;
	
	glm::vec2  posNull = (size / 2.0f) * -1.0f;
	glm::vec2  posOne = size / 2.0f;
	
	MeshData md;

	//! @todo create room mesh data
	//!    floor, walls, 'roof' and items
	// floor
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	
	vertices.push_back( posNull.x ); vertices.push_back( 0 ); vertices.push_back( posNull.y );	// x, y, z
	vertices.push_back( 0 ); vertices.push_back( 1 ); vertices.push_back( 0 );	// normal
	vertices.push_back( 0 ); vertices.push_back( 0 );							// uv

	vertices.push_back( posOne.x ); vertices.push_back( 0 ); vertices.push_back( posNull.y );	// x, y, z
	vertices.push_back( 0 ); vertices.push_back( 1 ); vertices.push_back( 0 );	// normal
	vertices.push_back( size.x ); vertices.push_back( 0 );							// uv
	
	vertices.push_back( posOne.x ); vertices.push_back( 0 ); vertices.push_back( posOne.y );	// x, y, z
	vertices.push_back( 0 ); vertices.push_back( 1 ); vertices.push_back( 0 );	// normal
	vertices.push_back( size.x ); vertices.push_back( size.y );							// uv
	
	vertices.push_back( posNull.x ); vertices.push_back( 0 ); vertices.push_back( posOne.y );	// x, y, z
	vertices.push_back( 0 ); vertices.push_back( 1 ); vertices.push_back( 0 );	// normal
	vertices.push_back( 0 ); vertices.push_back( size.y );							// uv
	
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(0);

	indices.push_back(3);
	indices.push_back(2);
	indices.push_back(0);
	
	md.iCount = indices.size();
	md.iData = indices.data();
	md.vCount = vertices.size();
	md.vData = vertices.data();
	m_pMeshFloor = pRenderer->LoadMesh(&md);

	// roof based on floor
	for( int i(0); i < 4; ++i)
		vertices[ (i * 8) + 1] = height;
	m_pMeshRoof = pRenderer->LoadMesh(&md);

	// wall
	vertices.clear();
	indices.clear();
	
	//left
	vertices.push_back( posNull.x ); vertices.push_back( 0 ); vertices.push_back( posNull.y );	// x, y, z
	vertices.push_back( 0 ); vertices.push_back( 0 ); vertices.push_back( 1 );	// normal
	vertices.push_back( 0 ); vertices.push_back( 0 );							// uv

	vertices.push_back( posNull.x ); vertices.push_back( 0 ); vertices.push_back( posOne.y );	// x, y, z
	vertices.push_back( 0 ); vertices.push_back( 0 ); vertices.push_back( 1 );	// normal
	vertices.push_back( size.x ); vertices.push_back( 0 );							// uv
	
	vertices.push_back( posNull.x ); vertices.push_back( height ); vertices.push_back( posOne.y );	// x, y, z
	vertices.push_back( 0 ); vertices.push_back( 0 ); vertices.push_back( 1 );	// normal
	vertices.push_back( size.x ); vertices.push_back( height );							// uv
	
	vertices.push_back( posNull.x ); vertices.push_back( height ); vertices.push_back( posNull.y );	// x, y, z
	vertices.push_back( 0 ); vertices.push_back( 0 ); vertices.push_back( 1 );	// normal
	vertices.push_back( 0 ); vertices.push_back( height );							// uv
	
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(0);

	indices.push_back(3);
	indices.push_back(2);
	indices.push_back(0);
	//right
	vertices.push_back( posOne.x ); vertices.push_back( 0 ); vertices.push_back( posNull.y );	// x, y, z
	vertices.push_back( 0 ); vertices.push_back( 0 ); vertices.push_back( -1 );	// normal
	vertices.push_back( 0 ); vertices.push_back( 0 );							// uv

	vertices.push_back( posOne.x ); vertices.push_back( 0 ); vertices.push_back( posOne.y );	// x, y, z
	vertices.push_back( 0 ); vertices.push_back( 0 ); vertices.push_back( -1 );	// normal
	vertices.push_back( size.x ); vertices.push_back( 0 );							// uv
	
	vertices.push_back( posOne.x ); vertices.push_back( height ); vertices.push_back( posOne.y );	// x, y, z
	vertices.push_back( 0 ); vertices.push_back( 0 ); vertices.push_back( -1 );	// normal
	vertices.push_back( size.x ); vertices.push_back( height );							// uv
	
	vertices.push_back( posOne.x ); vertices.push_back( height ); vertices.push_back( posNull.y );	// x, y, z
	vertices.push_back( 0 ); vertices.push_back( 0 ); vertices.push_back( -1 );	// normal
	vertices.push_back( 0 ); vertices.push_back( height );							// uv
	
	indices.push_back(4);
	indices.push_back(5);
	indices.push_back(6);

	indices.push_back(4);
	indices.push_back(6);
	indices.push_back(7);
	//up
	//down

	md.iCount = indices.size();
	md.iData = indices.data();
	md.vCount = vertices.size();
	md.vData = vertices.data();
	m_pMeshWalls = pRenderer->LoadMesh(&md);

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
	m_pMaterialFloor->Apply( m_Transform );
	m_pMeshFloor->Draw();

	m_pMaterialWalls->Apply( m_Transform );
	m_pMeshWalls->Draw();

	// only draw roof when room is not visible
	//m_pMeshRoof->Draw();
}

