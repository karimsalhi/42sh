#include "print_ast.h"

static char **create_part_one(void)
{
    char **token = xmalloc(sizeof(*token) * 20);
    token[0] = "root";
    token[1] = "input";
    token[2] = "list";
    token[3] = "and_or";
    token[4] = "pipeline";
    token[5] = "command";
    token[6] = "simple_command";
    token[7] = "shell_command";
    token[8] = "rule_if";
    token[9] = "compound_list";
    token[10] = "ionumber";
    token[11] = "redirect_output";
    token[12] = "redirect_input";
    token[13] = "redirect_append_output";
    token[14] = "redirect_dup_input";
    return token;
}

static char **create_part_two(void)
{
    char **token = xmalloc(sizeof(*token) * 20);
    token[0] = "redirect_dup_output";
    token[1] = "redirect_read_write";
    token[2] = "assignement";
    token[3] = "list_redirection";
    token[4] = "list_assignement";
    token[5] = "list_word";
    token[6] = "else_clause";
    token[7] = "funcdec";
    token[8] = "do_group";
    token[9] = "while";
    token[10] = "until";
    token[11] = "case_item";
    token[12] = "case_clause";
    token[13] = "rule_case";
    token[14] = "rule_for";
    token[15] = "word";
    token[16] = "word";
    return token;
}

static const char *type_to_str(struct ast_node *node, char **tab_one,
                               char **tab_two)
{
    if (node->type == NODE_WORD)
        return node->data;

    int pos = node->type;
    char *res;

    if (pos < 15)
        res = tab_one[pos];
    else
        res = tab_two[pos - 15];

    return res;
}

static int print_nodes(struct ast_node *node, int id, FILE *file)
{
    int self_id = id;

    char **tab_one = create_part_one();
    char **tab_two = create_part_two();

    for (size_t i = 0; i < node->nb_children; ++i)
    {
        fprintf(file, "\t<%d %s> -> <%d %s>\n", self_id,
                type_to_str(node, tab_one, tab_two), id + 1,
                type_to_str(*(node->children + i), tab_one, tab_two));
        id = print_nodes(*(node->children + i), id + 1, file);
    }

    free(tab_one);
    free(tab_two);

    return id;
}

void print_ast(struct ast_node *node)
{
    FILE *file = fopen("ast_print.dot", "w+");
    fprintf(file, "digraph G {\n");
    if (node)
        print_nodes(node, 0, file);
    fprintf(file, "}");

    fclose(file);
}
