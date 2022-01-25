#include <stdio.h>

#include "token/token_list.h"
#include "virtual_machine/virtual_machine.h"

int main()
{
	struct virtual_machine* vm = vm_create();

	token_list_push(&vm->token_list, token_create(TOKEN_PUSH, 2));
	token_list_push(&vm->token_list, token_create(TOKEN_PUSH, 4));
	token_list_push(&vm->token_list, token_create(TOKEN_ADD, 0));
	token_list_push(&vm->token_list, token_create(TOKEN_PUSH, 2));
	token_list_push(&vm->token_list, token_create(TOKEN_PUSH, 2));
	token_list_push(&vm->token_list, token_create(TOKEN_JUMP_COMPARE, 6));
	token_list_push(&vm->token_list, token_create(TOKEN_PUSH, 444));
	token_list_push(&vm->token_list, token_create(TOKEN_PUSH, 555));

	vm_start(vm);

	stack_peek(vm->stack);
	printf("peek: %lld \n", vm->stack->cached_data);

	return 0;
}