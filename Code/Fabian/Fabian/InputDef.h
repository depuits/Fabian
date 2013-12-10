#ifndef FABIAN_INPUTDEF_H_
#define FABIAN_INPUTDEF_H_

//******************************************
// Enum KeyState:
// the states a key can be in
//******************************************
enum KeyState : unsigned char
{
	UP			= 0x00,
	DOWN		= 0x01,
	DOWN_NEW	= 0x03	// 3 because when its a new down then it is also just down
};

//******************************************
// enum FKey:
// the key values for specific key
//******************************************
enum FKey : unsigned char
{
	FKEY_MLBUTTON		= 0x01,
	FKEY_MRBUTTON		= 0x02,
	FKEY_MMBUTTON		= 0x03,
	FKEY_MXBUTTON1		= 0x04,
	FKEY_MXBUTTON2		= 0x05,
	
	FKEY_H_VMOUSEMAX	= 0x05, // the max mouse value
	
	FKEY_BACK			= 0x08,
	FKEY_TAB			= 0x09,
	
	FKEY_CLEAR			= 0x0C,
	FKEY_RETURN			= 0x0D,
	
	FKEY_SHIFT			= 0x10,
	FKEY_CONTROL		= 0x11,
	FKEY_MENU			= 0x12,
	FKEY_PAUSE			= 0x13,
	FKEY_CAPITOL		= 0x14,
	
	FKEY_ESCAPE			= 0x1B,
	FKEY_SPACE			= 0x20,

	FKEY_PAGEUP			= 0x21,
	FKEY_PAGEDOWN		= 0x22,
	FKEY_END			= 0x23,
	FKEY_HOME			= 0x24,

	FKEY_LEFT			= 0x25,
	FKEY_UP				= 0x26,
	FKEY_RIGHT			= 0x27,
	FKEY_DOWN			= 0x28,
	
	FKEY_SNAPSHOT		= 0x2C,
	FKEY_INSERT			= 0x2D,
	FKEY_DELETE			= 0x2E,
	FKEY_HELP			= 0x2F,
	
	FKEY_0				= 0x30,
	FKEY_1				= 0x31,
	FKEY_2				= 0x32,
	FKEY_3				= 0x33,
	FKEY_4				= 0x34,
	FKEY_5				= 0x35,
	FKEY_6				= 0x36,
	FKEY_7				= 0x37,
	FKEY_8				= 0x38,
	FKEY_9				= 0x39,
	
	FKEY_A				= 0x41,
	FKEY_B				= 0x42,
	FKEY_C				= 0x43,
	FKEY_D				= 0x44,
	FKEY_E				= 0x45,
	FKEY_F				= 0x46,
	FKEY_G				= 0x47,
	FKEY_H				= 0x48,
	FKEY_I				= 0x49,
	FKEY_J				= 0x4A,
	FKEY_K				= 0x4B,
	FKEY_L				= 0x4C,
	FKEY_M				= 0x4D,
	FKEY_N				= 0x4E,
	FKEY_O				= 0x4F,
	FKEY_P				= 0x50,
	FKEY_Q				= 0x51,
	FKEY_R				= 0x52,
	FKEY_S				= 0x53,
	FKEY_T				= 0x54,
	FKEY_U				= 0x55,
	FKEY_V				= 0x56,
	FKEY_W				= 0x57,
	FKEY_X				= 0x58,
	FKEY_Y				= 0x59,
	FKEY_Z				= 0x5A,
	
	FKEY_GUI			= 0x5B,
	FKEY_LGUI			= 0x5C,
	FKEY_RGUI			= 0x5D,

	FKEY_NP_0			= 0x60,
	FKEY_NP_1			= 0x61,
	FKEY_NP_2			= 0x62,
	FKEY_NP_3			= 0x63,
	FKEY_NP_4			= 0x64,
	FKEY_NP_5			= 0x65,
	FKEY_NP_6			= 0x66,
	FKEY_NP_7			= 0x67,
	FKEY_NP_8			= 0x68,
	FKEY_NP_9			= 0x69,
	
	FKEY_NP_MULTIPLY	= 0x6A,
	FKEY_NP_ADD			= 0x6B,
	FKEY_NP_SEPERATOR	= 0x6C,
	FKEY_NP_SUBSTRACT	= 0x6D,
	FKEY_NP_DECIMAL		= 0x6E,
	FKEY_NP_DIVIDE		= 0x6F,
	
	FKEY_F1				= 0x70,
	FKEY_F2				= 0x71,
	FKEY_F3				= 0x72,
	FKEY_F4				= 0x73,
	FKEY_F5				= 0x74,
	FKEY_F6				= 0x75,
	FKEY_F7				= 0x76,
	FKEY_F8				= 0x77,
	FKEY_F9				= 0x78,
	FKEY_F10			= 0x79,
	FKEY_F11			= 0x7A,
	FKEY_F12			= 0x7B,
	FKEY_F13			= 0x7C,
	FKEY_F14			= 0x7D,
	FKEY_F15			= 0x7E,
	FKEY_F16			= 0x7F,
	FKEY_F17			= 0x80,
	FKEY_F18			= 0x81,
	FKEY_F19			= 0x82,
	FKEY_F20			= 0x83,
	FKEY_F21			= 0x84,
	FKEY_F22			= 0x85,
	FKEY_F23			= 0x86,
	FKEY_F24			= 0x87,
	
	FKEY_NUMLOCK		= 0x90,
	FKEY_SCROLL			= 0x91,
	
	FKEY_LSHIFT			= 0xA0,
	FKEY_RSHIFT			= 0xA1,
	FKEY_LCONTROL		= 0xA2,
	FKEY_RCONTROL		= 0xA3,
	FKEY_LMENU			= 0xA4,
	FKEY_RMENU			= 0xA5,

	FKEY_H_VKEYSMAX		= 0xA5, // the max key value
};

#endif //FABIAN_INPUTDEF_H_
