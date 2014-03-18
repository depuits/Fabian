#ifndef FABIAN_INPUTDEF_H_
#define FABIAN_INPUTDEF_H_

/** @file */ 

/*! Enum KeyState (flags): 
 * the states a key can be in
 */
enum KeyState : unsigned char
{
	UP			= 0x00,	/*!< Key is up */
	DOWN		= 0x01,	/*!< Key is down */
	DOWN_NEW	= 0x03	/*!< Key is down and it wasn't */ // 3 because when its a new down then it is also just down
};

/*! enum FKey: 
 * the key values for specific key
 */
enum FKey : unsigned char
{
	FKEY_MLBUTTON		= 0x01,	/*!< Left mouse button */
	FKEY_MRBUTTON		= 0x02,	/*!< Right mouse button */
	FKEY_MMBUTTON		= 0x03,	/*!< Middle mouse button */
	FKEY_MXBUTTON1		= 0x04,	/*!< Extra mouse button 1 */
	FKEY_MXBUTTON2		= 0x05,	/*!< Extra mouse button 2 */
	
	FKEY_H_VMOUSEMAX	= 0x05,	/*!< Max mouse input value */
	
	FKEY_BACK			= 0x08,	/*!< Backspace */
	FKEY_TAB			= 0x09,	/*!< Tab */
	
	FKEY_CLEAR			= 0x0C,	/*!< Clear key */
	FKEY_RETURN			= 0x0D,	/*!< Return key (enter) */
	
	FKEY_SHIFT			= 0x10,	/*!< Left or right shift */
	FKEY_CONTROL		= 0x11,	/*!< Left or right control */
	FKEY_MENU			= 0x12,	/*!< Left or right alt */
	FKEY_PAUSE			= 0x13,	/*!< Pause key */
	FKEY_CAPITOL		= 0x14,	/*!< Caps lock */
	
	FKEY_ESCAPE			= 0x1B,	/*!< Escape */
	FKEY_SPACE			= 0x20,	/*!< Space */

	FKEY_PAGEUP			= 0x21,	/*!< Page up */
	FKEY_PAGEDOWN		= 0x22,	/*!< Page down */
	FKEY_END			= 0x23,	/*!< End */
	FKEY_HOME			= 0x24,	/*!< Home */

	FKEY_LEFT			= 0x25,	/*!< Left arrow */
	FKEY_UP				= 0x26,	/*!< Up arrow */
	FKEY_RIGHT			= 0x27,	/*!< Right arrow */
	FKEY_DOWN			= 0x28,	/*!< Down arrow */
	
	FKEY_SNAPSHOT		= 0x2C,	/*!< Print screen key */
	FKEY_INSERT			= 0x2D,	/*!< Insert */
	FKEY_DELETE			= 0x2E,	/*!< Delete */
	FKEY_HELP			= 0x2F,	/*!< Help key */
	
	FKEY_0				= 0x30,	/*!< 0 key */
	FKEY_1				= 0x31,	/*!< 1 key */
	FKEY_2				= 0x32,	/*!< 2 key */
	FKEY_3				= 0x33,	/*!< 3 key */
	FKEY_4				= 0x34,	/*!< 4 key */
	FKEY_5				= 0x35,	/*!< 5 key */
	FKEY_6				= 0x36,	/*!< 6 key */
	FKEY_7				= 0x37,	/*!< 7 key */
	FKEY_8				= 0x38,	/*!< 8 key */
	FKEY_9				= 0x39,	/*!< 9 key */
	
	FKEY_A				= 0x41,	/*!< A key */
	FKEY_B				= 0x42,	/*!< B key */
	FKEY_C				= 0x43,	/*!< C key */
	FKEY_D				= 0x44,	/*!< D key */
	FKEY_E				= 0x45,	/*!< E key */
	FKEY_F				= 0x46,	/*!< F key */
	FKEY_G				= 0x47,	/*!< G key */
	FKEY_H				= 0x48,	/*!< H key */
	FKEY_I				= 0x49,	/*!< I key */
	FKEY_J				= 0x4A,	/*!< J key */
	FKEY_K				= 0x4B,	/*!< K key */
	FKEY_L				= 0x4C,	/*!< L key */
	FKEY_M				= 0x4D,	/*!< M key */
	FKEY_N				= 0x4E,	/*!< N key */
	FKEY_O				= 0x4F,	/*!< O key */
	FKEY_P				= 0x50,	/*!< P key */
	FKEY_Q				= 0x51,	/*!< Q key */
	FKEY_R				= 0x52,	/*!< R key */
	FKEY_S				= 0x53,	/*!< S key */
	FKEY_T				= 0x54,	/*!< T key */
	FKEY_U				= 0x55,	/*!< U key */
	FKEY_V				= 0x56,	/*!< V key */
	FKEY_W				= 0x57,	/*!< W key */
	FKEY_X				= 0x58,	/*!< X key */
	FKEY_Y				= 0x59,	/*!< Y key */
	FKEY_Z				= 0x5A,	/*!< Z key */
	
	FKEY_GUI			= 0x5B,	/*!< Left or right Windows or mac key */
	FKEY_LGUI			= 0x5C,	/*!< Left Windows or mac key */
	FKEY_RGUI			= 0x5D,	/*!< Right Windows or mac key */

	FKEY_NP_0			= 0x60,	/*!< Numpad 0 */
	FKEY_NP_1			= 0x61,	/*!< Numpad 1 */
	FKEY_NP_2			= 0x62,	/*!< Numpad 2 */
	FKEY_NP_3			= 0x63,	/*!< Numpad 3 */
	FKEY_NP_4			= 0x64,	/*!< Numpad 4 */
	FKEY_NP_5			= 0x65,	/*!< Numpad 5 */
	FKEY_NP_6			= 0x66,	/*!< Numpad 6 */
	FKEY_NP_7			= 0x67,	/*!< Numpad 7 */
	FKEY_NP_8			= 0x68,	/*!< Numpad 8 */
	FKEY_NP_9			= 0x69,	/*!< Numpad 9 */
	
	FKEY_NP_MULTIPLY	= 0x6A,	/*!< Numpad multiply */
	FKEY_NP_ADD			= 0x6B,	/*!< Numpad add */
	FKEY_NP_SEPERATOR	= 0x6C,	/*!< Numpad seperator */
	FKEY_NP_SUBSTRACT	= 0x6D,	/*!< Numpad substract */
	FKEY_NP_DECIMAL		= 0x6E,	/*!< Numpad decimal */
	FKEY_NP_DIVIDE		= 0x6F,	/*!< Numpad divide */
	
	FKEY_F1				= 0x70,	/*!< Function key 1 */
	FKEY_F2				= 0x71,	/*!< Function key 2 */
	FKEY_F3				= 0x72,	/*!< Function key 3 */
	FKEY_F4				= 0x73,	/*!< Function key 4 */
	FKEY_F5				= 0x74,	/*!< Function key 5 */
	FKEY_F6				= 0x75,	/*!< Function key 6 */
	FKEY_F7				= 0x76,	/*!< Function key 7 */
	FKEY_F8				= 0x77,	/*!< Function key 8 */
	FKEY_F9				= 0x78,	/*!< Function key 9 */
	FKEY_F10			= 0x79,	/*!< Function key 10 */
	FKEY_F11			= 0x7A,	/*!< Function key 11 */
	FKEY_F12			= 0x7B,	/*!< Function key 12 */
	FKEY_F13			= 0x7C,	/*!< Function key 13 */
	FKEY_F14			= 0x7D,	/*!< Function key 14 */
	FKEY_F15			= 0x7E,	/*!< Function key 15 */
	FKEY_F16			= 0x7F,	/*!< Function key 16 */
	FKEY_F17			= 0x80,	/*!< Function key 17 */
	FKEY_F18			= 0x81,	/*!< Function key 18 */
	FKEY_F19			= 0x82,	/*!< Function key 19 */
	FKEY_F20			= 0x83,	/*!< Function key 20 */
	FKEY_F21			= 0x84,	/*!< Function key 21 */
	FKEY_F22			= 0x85,	/*!< Function key 22 */
	FKEY_F23			= 0x86,	/*!< Function key 23 */
	FKEY_F24			= 0x87,	/*!< Function key 24 */
	
	FKEY_NUMLOCK		= 0x90,	/*!< Num lock key */
	FKEY_SCROLL			= 0x91,	/*!< Scroll lock key */
	
	FKEY_LSHIFT			= 0xA0,	/*!< Left shift */
	FKEY_RSHIFT			= 0xA1,	/*!< Right shift */
	FKEY_LCONTROL		= 0xA2,	/*!< Left control */
	FKEY_RCONTROL		= 0xA3,	/*!< Right control */
	FKEY_LMENU			= 0xA4,	/*!< Left alt */
	FKEY_RMENU			= 0xA5,	/*!< Right alt */

	FKEY_H_VKEYSMAX		= 0xA5,	/*!< Max keyboard input value */
};

#endif //FABIAN_INPUTDEF_H_
