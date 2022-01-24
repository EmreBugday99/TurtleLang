#pragma once
#ifndef TOKEN_LIST_H
#define TOKEN_LIST_H

#include "token.h"
#include "../types.h"

typedef struct
{
	token* list;
	size_t elements;
	size_t capacity;
} token_list;

/// <summary>
/// Creates & initializes a new token_list
/// </summary>
/// <param name="capacity">Amount of tokens this token_list can store initially.</param>
/// <returns>Newly created token</returns>
token_list token_list_create(size_t capacity);
/// <summary>
/// Pushes a new token to the end of the token_list. \n Increases capacity if needed.
/// </summary>
/// <param name="list">token_list to push at.</param>
/// <param name="token_to_push">The token that's being pushed into the token_list.</param>
void token_list_push(token_list* list, token token_to_push);
/// <summary>
///  Inserts a new token into the specified index. \n Increases capacity if needed.
/// </summary>
/// <param name="list">token_list to insert at</param>
/// <param name="index">index to insert at</param>
/// <param name="token_to_insert">The token that's being inserted into the token_list.</param>
/// <returns>returns 1 if successful, returns 0 if failed to insert.</returns>
vm_result token_list_insert(token_list* list, size_t index, token token_to_insert);
/// <summary>
/// Deletes a token from the specified index.
/// </summary>
/// <param name="list">token_list to delete from.</param>
/// <param name="index">index of the token that's being deleted.</param>
/// <returns>returns 1 if successful, returns 0 if failed to insert.</returns>
vm_result token_list_delete(token_list* list, size_t index);
/// <summary>
/// Copies all the contents of one token_list to another token_list.
/// </summary>
/// <param name="copy_from">token_list to copy from.</param>
/// <param name="copy_to">token_list to copy to.</param>
void token_list_copy(const token_list* copy_from, token_list* copy_to);
/// <summary>
/// Increases capacity of the token_list.
/// </summary>
/// <param name="list">token_list to increase capacity.</param>
/// <param name="increase_count">How many more tokens this token_list needs to have?</param>
void token_list_increase_capacity(token_list* list, size_t increase_count);

#endif