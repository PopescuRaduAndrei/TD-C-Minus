#ifndef __AST_H
#define __AST_H

#define MAX_Node_TYPE 50
#define MAX_EXTRA_DATA 50

typedef struct node {
	char type[MAX_Node_TYPE];
	int numLinks;
	char extraData[MAX_EXTRA_DATA];
	struct node** links;
} Node;

Node* createDefaultNode(const char* nodeName, unsigned int linksCount);
Node* resizeNodeLinks(Node* nodeToResize, unsigned int newSize);
Node* createListNode(const char* listName, Node* firstLink);
void  addLinkToList(Node* listNode, Node* linkToAdd);
Node* createProgramUnitNode(Node* declaration);
Node* createDeclarationNode(Node* varFunDeclaration);
Node* createIfStatement(Node* expression, Node* thenStatement, Node* elseStatement);
Node* createIterationStatementNode(Node* expression, Node* statement);
Node* createFunctionDeclarationNode(Node* typeSpecifier, const char* functionName, Node* params, Node* compoundStatement);
Node* createTypeSpecifier(const char* typeName);
Node* createVariableNode(const char* identifierName, Node* expression);
Node* createVarDeclaration(Node* typeSpecifier, const char* varName, int value);
Node* createCompoundStatement(Node* localDeclList, Node* statementList);
Node* createStatementNode(Node* statementDeclaration);
Node* createExpressionStatement(Node* expressionDeclaration);
Node* createReturnStatement(Node* expressionDeclaration);
Node* createExpressionNode(Node* expressionDeclaration);
Node* createParametersDeclarationNode(Node* parametersDeclaration);
Node* createRelationalOperatorNode(const char* operatorType);
Node* createAddSubOperatorNode(const char* opratorType);
Node* createMulDivOperatorNode(const char* operatorType);
Node* newSimpExp(Node* addExp1, Node* relop, Node* addExp2);
Node* newAddExp(Node* addExp, Node* addop, Node* term);
Node* newTerm(Node* term, Node* mulop, Node* factor);
Node* newCall(char* ID, Node* args);
Node* newArgList(Node* argList);
Node* newNumNode(Node* expression, int val);

void printAst(Node* ast, int level);
#endif