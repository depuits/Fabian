////////////////////////////////////////////
// Used only for compiling header only files
////////////////////////////////////////////
 
#define COMPILE_HEADER_ONLY

#ifdef COMPILE_HEADER_ONLY // only compile headers when specified

// hpp files
#include "CCompBase.hpp"
#include "CCompCamera.hpp"
#include "CCompControl.hpp"
#include "CCompModel.hpp"
#include "CGameObject.hpp"
#include "CLibrary.hpp"
#include "CServiceBase.hpp"
#include "CTransform.hpp"

// data defines
#include "DataStructures.h"
#include "InputDef.h"
#include "LogDef.h"
#include "ServiceMsg.h"

// interfaces
#include "ICamera.h"
#include "IComponent.h"
#include "IContentManager.h"
#include "IGlobalAccessor.h"
#include "IImage.h"
#include "IInput.h"
#include "IKernel.h"
#include "ILogger.h"
#include "IMaterial.h"
#include "IMesh.h"
#include "IRenderer.h"
#include "IService.h"
#include "IShader.h"

#endif