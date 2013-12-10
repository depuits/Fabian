#ifndef FABIAN_DATASTRUCTURES_H_
#define FABIAN_DATASTRUCTURES_H_


#ifdef __cplusplus
extern "C"
{
#endif
	
	typedef struct MeshData
	{
		float *vData;
		int vCount;
		unsigned int *iData;
		int iCount;
	} MeshData;

	typedef struct ImageData
	{
		unsigned w;
		unsigned h;
		unsigned char *data;
	} ImageData;


#ifdef __cplusplus
}
#endif


#endif //FABIAN_DATASTRUCTURES_H_
