#ifndef FABIAN_DATASTRUCTURES_H_
#define FABIAN_DATASTRUCTURES_H_

#ifdef __cplusplus
extern "C"
{
#endif
	
	////////////////////////////////////////////
	//! Struct MeshData: 
	//! data structure holding the information needed 
	//! for creating meshes
	////////////////////////////////////////////
	typedef struct MeshData
	{
		/// Pointer to the vertex data
		float *vData;
		/// Vertex count
		int vCount;
		/// Pointer to the indices
		unsigned int *iData;
		/// index count
		int iCount;
	} MeshData;

	////////////////////////////////////////////
	//! Struct ImageData: 
	//! data structure holding the information needed 
	//! for creating images/textures
	////////////////////////////////////////////
	typedef struct ImageData
	{
		/// Image width
		unsigned w;
		/// Image height
		unsigned h;
		/// Image pixel data
		unsigned char *data;
	} ImageData;


#ifdef __cplusplus
}
#endif


#endif //FABIAN_DATASTRUCTURES_H_
