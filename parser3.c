
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern int i;
void json_parse_init(JSONContext *ctx, const char *json) {
    ctx->json = json;
    ctx->position = 0;
}

// Skips whitespace in the JSON string
static void skip_whitespace(JSONContext *ctx) {
    while (isspace(ctx->json[ctx->position])) {
        ctx->position++;
    }
}

// Parses the next key-value pair
int json_parse_next(JSONContext *ctx, JSONPair *pair) {
    skip_whitespace(ctx);

    // Check if end of JSON or end of object
    if (ctx->json[ctx->position] == '}' || ctx->json[ctx->position] == '\0') {
        return 0; // No more pairs
    }

    // Expecting key
    if (ctx->json[ctx->position] != '{') {
        return -1; // Malformed JSON
    }

    ++ctx->position;//skip the curly brace

    label:

    skip_whitespace(ctx);
    int start = ++ctx->position; // Skip the opening quote
    while (ctx->json[ctx->position] != '"' && ctx->json[ctx->position] != '\0') {
        ctx->position++;
    }

    // Allocate and set key
    int keyLength = ctx->position - start;
    pair[i].key = (char *)malloc(keyLength + 1);
    strncpy(pair[i].key, ctx->json + start, keyLength);
    pair[i].key[keyLength] = '\0';

    ctx->position++; // Skip the closing quote

    // Expecting colon
    skip_whitespace(ctx);
    if (ctx->json[ctx->position++] != ':') {
        free(pair->key);
        return -1; // Malformed JSON
    }

    skip_whitespace(ctx);

    // Expecting value (simplified to handle strings only)
    if (ctx->json[ctx->position] != '"') {
        free(pair->key);
        return -1; // Malformed JSON
    }

    start = ++ctx->position; // Skip the opening quote
    while (ctx->json[ctx->position] != '"' && ctx->json[ctx->position] != '\0') {
        ctx->position++;
    }

    // Allocate and set value
    int valueLength = ctx->position - start;
    pair[i].value = (char *)malloc(valueLength + 1);
    strncpy(pair[i].value, ctx->json + start, valueLength);
    pair[i].value[valueLength] = '\0';

    ctx->position++; // Skip the closing quote

    skip_whitespace(ctx);
    if (ctx->json[ctx->position] == ',') {
        ctx->position++; // Skip comma if there is another pair
        i++;
        goto label;
    }

    return 1; // Success
}
