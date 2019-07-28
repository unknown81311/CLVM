extern "C" {
#include "Lua\lua.h"
#include "Lua\lua.hpp"
#include "Lua\lualib.h"
#include "Lua\lauxlib.h"
#include "Lua\luaconf.h"
#include "Lua\llimits.h"
#include "Lua/ldo.h"
}

#include <Windows.h>

union r_Value {
	PVOID gc;
	PVOID p;
	double n;
	int b;
};
struct r_TValue {
	r_Value value;
	int tt;
};

#define Format(x)(x - 0x400000 + (DWORD)GetModuleHandle(NULL))
#define Declare(address, returnValue, callingConvention, ...) (returnValue(callingConvention*)(__VA_ARGS__))(Format(address))
auto rluaM_realloc_ = Declare(0x820f60, void*, __cdecl, uintptr_t rL, void *block, size_t osize, size_t nsize, unsigned int modkey);

#define rluaM_malloc(L,a,b) rluaM_realloc_(L, NULL, NULL, a, b)

class RobloxModKeys {
public:
	int UserData = 0,
		TString = 2,
		TValue = 3,
		LClosure = 4,
		UpValue = 5,
		Proto = 6,
		Thread = 7,
		Table = 8;
};
RobloxModKeys ModKeys;

namespace VMOffsets {
	LClosure *VmClosure;
	TValue *VmTvalue;
	StkId VmStk;
	const Instruction *VmInstr;
}

#define STACK 16
#define BASE 20
#define TOP 8

void Convert(lua_State* Lua, DWORD Roblox, int SomeValueLOL) {
	lua_assert(isLua(Lua->ci));
	VMOffsets::VmInstr = Lua->savedpc;
	VMOffsets::VmClosure = &clvalue(Lua->ci->func)->l;
	VMOffsets::VmStk = Lua->base;
	VMOffsets::VmTvalue = VMOffsets::VmClosure->p->k;

	r_TValue* RobloxTValue = (r_TValue*)rluaM_malloc(Roblox, VMOffsets::VmClosure->p->sizek * sizeof(r_TValue), ModKeys.TValue);
	for (int Iterator = 0; Iterator < VMOffsets::VmClosure->p->sizek; Iterator++) {
		//Add conversion
	}
	
	DWORD Base = *(DWORD*)(Roblox + BASE);
	*(DWORD*)(Roblox + TOP) += VMOffsets::VmClosure->p->sizek * STACK;
	while (true) {
		const Instruction Current = *VMOffsets::VmInstr++;

		//write encs

	}
}
