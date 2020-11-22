#ifndef __AST_H
#define __AST_H

#define MAX_Node_TYPE 50
#define MAX_EXTRA_DATA 50

typedef struct Node {
	char type[MAX_Node_TYPE];
	int numLinks;
	char extraData[MAX_EXTRA_DATA];
	struct Node* links;
} Node;

Node* newDecList(Node* decList, Node* declaration);
Node* newDec(Node* declaration, int type);
Node* newVarDec(Node* typeSpecifier, const char* varName, int value);
Node* newTypeSpe(const char* typeName);
Node* newFunDec(Node* typeSpecifier, const char* functionName, Node* paramsList, Node* compoundStatement);
Node* newParams(Node* paramList, Node* typeSpecifier);
Node* newParamList(Node* paramList, Node* param);
Node* newParam(Node* typeSpecifier, char* ID);
Node* newCompound(Node* localDecs, Node* stmtList);
Node* newLocalDecs(Node* localDecs, Node* varDec);
Node* newStmtList(Node* stmtList, Node* stmt);
Node* newExpStmt(Node* expression);
Node* newSelectStmt(Node* expression, Node* stmt, Node* elseStmt);
Node* newIterStmt(Node* expression, Node* stmt);
Node* newRetStmt(Node* expression);
Node* newAssignExp(Node* var, Node* expressio);
Node* newVar(char* ID);
Node* newSimpExp(Node* addExp1, int relop, Node* addExp2);
Node* newAddExp(Node* addExp, int addop, Node* term);
Node* newTerm(Node* term, int mulop, Node* factor);

Node* newNumNode(int num);

Node* newCall(char* ID, Node* args);
Node* newArgList(Node* argList, Node* expression);


Node* createDefaultNode(const char* nodeName, unsigned int linksCount);
Node* resizeNodeLinks(Node* nodeToResize, unsigned int newSize);
Node* createListNode(const char* listName, Node* firstLink);
void addLinkToList(Node* listNode, Node* linkToAdd);
void printAst(Node* ast, int level);

#endif