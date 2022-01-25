#include <stdlib.h>

#include "data_types/list.h"
#include "token/token.h"
#include "token/token_type.h"
#include "virtual_machine/virtual_machine.h"

int main()
{
	void* token1 = token_create(TOKEN_PUSH, 5);
	void* token2 = token_create(TOKEN_PUSH, 10);
	void* token3 = token_create(TOKEN_ADD, 0);

	struct virtual_machine* vm = vm_create();
	list_add(vm->token_list, token1);
	list_add(vm->token_list, token2);
	list_add(vm->token_list, token3);

	vm_start(vm);

	free(vm->token_list);
	free(vm);
	free(token1);
	free(token2);
	free(token3);
	return 0;
}