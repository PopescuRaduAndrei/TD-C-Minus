#include "ast.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>

Node* newDecList(Node* decList, Node* declaration) {

}

Node* newDec(Node* declaration, int type) {
	Node* retNode = createDefaultNode("Declaration", 1);
	if (retNode)
	{
		retNode->links[0] = declaration;
	}
	return retNode;
}

Node* newVarDec(Node* typeSpecifier, const char* varName, int value) {
	Node* retNode = createDefaultNode("VariableDeclaration", 2);

	if (retNode)
	{
		retNode->links[0] = typeSpecifier;
		if (varName)
			sprintf(retNode->extraData, "%s", varName);
		retNode->links[1] = createDefaultNode("IntValue", 0);
		sprintf(retNode->links[1]->extraData, "%d", value);
	}

	return retNode;
}

Node* newTypeSpe(const char typeName) {
	Node* retVal = createDefaultNode("TypeSpecifier", 0);
	if (typeName)
		sprintf(retVal->extraData, "%s", typeName);
	return retVal;
}

Node* newParams(Node* paramList, Node* typeSpecifier) {

}

Node* newParamList(Node* paramList, Node* param) {

}

Node* newParam(Node* typeSpecifier, char* ID) {

}

Node* newCompound(Node* localDecs, Node* stmtList) {
	Node* retNode = createDefaultNode("CompoundStatement", 2);
	retNode->links[0] = localDecs;
	retNode->links[1] = stmtList;
	return retNode;
}

Node* newLocalDecs(Node* localDecs, Node* varDec) {

}

Node* newStmtList(Node* stmtList, Node* stmt) {

}

Node* newExpStmt(Node* expression) {

}

Node* newSelectStmt(Node* expression, Node* stmt, Node* elseStmt) {

}

Node* newIterStmt(Node* expression, Node* stmt) {

}

Node* newRetStmt(Node* expression) {

}

Node* newAssignExp(Node* var, Node* expressio) {

}

Node* newVar(char ID) {

}

Node* newSimpExp(Node addExp1, int relop, Node* addExp2) {

}

Node* newAddExp(Node* addExp, int addop, Node* term) {

}

Node* newTerm(Node* term, int mulop, Node* factor) {

}

Node* newNumNode(int num) {

}

Node* newCall(char ID, Node* args) {

}

Node* newArgList(Node* argList, Node* expression) {

}

Node* createDefaultNode(const char* nodeName, unsigned int linksCount)
{
	Node* retNode = (Node*)malloc(sizeof(Node));
	if (retNode)
	{
		memset(retNode, 0, sizeof(Node));
		if (nodeName)
		{
			strcpy(retNode->type, nodeName);
		}
		retNode->numLinks = linksCount;
		if (linksCount > 0)
		{
			retNode->links = (Node**)malloc(linksCount * sizeof(Node*));
		}
	}
	return retNode;
}

Node* resizeNodeLinks(Node* nodeToResize, unsigned int newSize)
{
	if (nodeToResize->numLinks == 0)
	{
		nodeToResize->links = (Node**)malloc(newSize * sizeof(Node*));
	}
	else
	{
		nodeToResize->links = (Node**)realloc(nodeToResize->links, newSize * sizeof(Node*));
	}
	nodeToResize->numLinks = newSize;
	return nodeToResize;
}

Node* createListNode(const char* listName, Node* firstLink)
{
	Node* retNode = createDefaultNode(listName, 1);
	retNode->links[0] = firstLink;
	return retNode;
}
void addLinkToList(Node* listNode, Node* linkToAdd)
{
	unsigned int numLinks = listNode->numLinks;
	resizeNodeLinks(listNode, numLinks + 1);
	listNode->links[numLinks] = linkToAdd;
}

Node* newFunDec(Node* typeSpecifier, const char* functionName, Node* paramsList, Node* compoundStatement)
{

	Node* retNode = createDefaultNode("FunctionDefinition", 3);

	if (retNode)
	{
		retNode->links[0] = typeSpecifier;
		retNode->links[1] = paramsList;
		retNode->links[2] = compoundStatement;
		if (functionName)
			strcpy(retNode->extraData, functionName);
	}

	return retNode;
}


Node* createTypeSpecifier(const char* typeName)
{
	Node* retVal = createDefaultNode("TypeSpecifier", 0);
	if (typeName)
		sprintf(retVal->extraData, "%s", typeName);
	return retVal;
}

void printAst(Node* ast, int level)
{
	int idx = 0;
	if (ast)
	{
		for (idx = 0; idx < level; idx++)
		{
			printf(" ");
		}
		if (ast->type)
		{
			printf("%s ", ast->type);
		}
		if (ast->numLinks)
		{
			printf(" - %d - %s\n", ast->numLinks, ast->extraData);
		}
		else
		{
			printf(" - %s\n", ast->extraData);
		}
		for (idx = 0; idx < ast->numLinks; idx++)
		{

			printAst(ast->links[idx], level + 1);
		}
	}
}
