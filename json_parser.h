#ifndef JSON_PARSER_H
#define JSON_PARSER_H

// JSON key-value pair structure
typedef struct {
    char *key;
    char *value;
} JSONPair;

// JSON parser context
typedef struct {
    const char *json;
    int position;
} JSONContext;

// Function prototypes
void json_parse_init(JSONContext *ctx, const char *json);
int json_parse_next(JSONContext *ctx, JSONPair *pair);

#endif // JSON_PARSER_H

