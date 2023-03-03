#ifndef PARSER_H
#define PARSER_H

#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../lexer/lexer.h"
#include "../utils/xmalloc.h"
#include "node_type.h"
#include "redirection/redirection.h"

struct ast_node
{
    enum node_type type;
    size_t nb_children;
    struct ast_node **children;
    char *data;
};
/**
 * \brief Create an ast from the input
 *
 * \param opt option
 * \param argc argc
 * \param argv argv
 */
struct ast_node *parser(struct option *opt, int argc, char **argv);

/**
 * \brief add a node to ast
 *
 * \param node ast_node (root)
 * \param tmp ast_node
 * \param lexer lexer
 */
size_t add_child(struct ast_node *node, struct ast_node *tmp,
                 struct lexer *lexer);

/**
 * \brief add data to a ast-node
 *
 * \param node ast_node
 * \param value data to add
 */
void add_node_data(struct ast_node *node, char *value);
/**
 * \brief free ast
 *
 * \param node ast_node
 */
void free_ast(struct ast_node *node);

/**
 * \brief Create the ast from the lexer
 *
 * \param lexer lexer
 */

struct ast_node *root(struct lexer *lexer);

/**
 * \brief Create a ast if the rule if is checked
 *
 * \param lexer lexer
 */
struct ast_node *rule_if(struct lexer *lexer);
/**
 * \brief Create a ast if the rule compund_list is checked
 *
 * \param lexer lexer
 */
struct ast_node *compound_list(struct lexer *lexer);
/**
 * \brief Create a ast if the rule else_clause is checked
 *
 * \param lexer lexer
 */
struct ast_node *else_clause(struct lexer *lexer);
/**
 * \brief Create a node with type
 *
 * \param type type
 */
struct ast_node *create_node(enum node_type type);
/**
 * \brief Create a node of element
 *
 * \param lexer lexer
 */
struct ast_node *element(struct lexer *lexer);
/**
 * \brief Create a ast if the rule command is checked
 *
 * \param lexer lexer
 */
struct ast_node *command(struct lexer *lexer);
/**
 * \brief Create a ast if the rule prefix is checked
 *
 * \param lexer lexer
 */
struct ast_node *prefix(struct lexer *lexer);
/**
 * \brief Create a ast if the rule simple_command is checked
 *
 * \param lexer lexer
 */
struct ast_node *simple_command(struct lexer *lexer);
/**
 * \brief Create a ast if the rule shell comamnd is checked
 *
 * \param lexer lexer
 */
struct ast_node *shell_command(struct lexer *lexer);
/**
 * \brief Create a ast if the rule pipeline is checked
 *
 * \param lexer lexer
 */
struct ast_node *pipeline(struct lexer *lexer);
/**
 * \brief Create a ast if the rule and_or is checked
 *
 * \param lexer lexer
 */
struct ast_node *and_or(struct lexer *lexer);
/**
 * \brief Create a ast if the rule input is checked
 *
 * \param lexer lexer
 */
struct ast_node *input(struct lexer *lexer);
/**
 * \brief Create a ast if the rule list is checked
 *
 * \param lexer lexer
 */
struct ast_node *list(struct lexer *lexer);

// struct ast_node *redirection(struct lexer *lexer);
/**
 * \brief Create a ast if the rule do_group is checked
 *
 * \param lexer lexer
 */
struct ast_node *do_group(struct lexer *lexer);
/**
 * \brief Create a ast if the rule while is checked
 *
 * \param lexer lexer
 */
struct ast_node *while_rule(struct lexer *lexer);
/**
 * \brief Create a ast if the rule until is checked
 *
 * \param lexer lexer
 */
struct ast_node *until_rule(struct lexer *lexer);
/**
 * \brief Create a ast if the rule case_item is checked
 *
 * \param lexer lexer
 */
struct ast_node *case_item(struct lexer *lexer);
/**
 * \brief Create a ast if the rule case_clause is checked
 *
 * \param lexer lexer
 */
struct ast_node *case_clause(struct lexer *lexer);
/**
 * \brief Create a ast if the rule case is checked
 *
 * \param lexer lexer
 */
struct ast_node *rule_case(struct lexer *lexer);
/**
 * \brief Create a ast if the rule for is checked
 *
 * \param lexer lexer
 */
struct ast_node *rule_for(struct lexer *lexer);

struct ast_node *funcdec(struct lexer *lexer);
#endif /* ! PARSER_H */
