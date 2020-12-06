#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

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

Node* createProgramUnitNode(Node* declaration)
{
	Node* retNode = createDefaultNode("ProgramUnit", 1);
	if (retNode)
	{
		retNode->links[0] = declaration;
	}

	return retNode;
}

Node* createDeclarationNode(Node* varFunDeclaration)
{
	Node* retNode = createDefaultNode("Declaration", 1);
	if (retNode)
	{
		retNode->links[0] = varFunDeclaration;
	}
	return retNode;
}

Node* createIfStatement(Node* expression, Node* thenStatement, Node* elseStatement)
{
	Node* retNode = createDefaultNode("IfStatement", 3);
	retNode->links[0] = expression;
	retNode->links[1] = thenStatement;
	retNode->links[2] = elseStatement;
	return retNode;
}

Node* createIterationStatementNode(Node* expression, Node* statement)
{
	Node* retNode = createDefaultNode("IterationStatement", 2);
	retNode->links[0] = expression;
	retNode->links[1] = statement;

	return retNode;
}

Node* createAddSubOperatorNode(const char* opratorType)
{
	Node* retVal = createDefaultNode("AddSubOperator", 0);
	if (opratorType)
		sprintf(retVal->extraData, "%s", opratorType);
	return retVal;
}

Node* createMulDivOperatorNode(const char* operatorType)
{
	Node* retVal = createDefaultNode("MulDivOperator", 0);
	if (operatorType)
		sprintf(retVal->extraData, "%s", operatorType);
	return retVal;
}

Node* createRelationalOperatorNode(const char* operatorType)
{
	Node* retVal = createDefaultNode("RelationalOperator", 0);
	if (operatorType)
		sprintf(retVal->extraData, "%s", operatorType);
	return retVal;
}

Node* createVariableNode(const char* identifierName, Node* expression)
{
	Node* retNode = createDefaultNode("Variable", 1);
	retNode->links[0] = expression;
	if (identifierName)
		sprintf(retNode->extraData, "%s", identifierName);

	return retNode;
}

Node* createFunctionDeclarationNode(Node* typeSpecifier, const char* functionName, Node* params, Node* compoundStatement)
{
	Node* retNode = createDefaultNode("FunctionDefinition", 3);

	if (retNode)
	{
		retNode->links[0] = typeSpecifier;
		retNode->links[1] = params;
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

Node* createVarDeclaration(Node* typeSpecifier, const char* varName, int value)
{
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

Node* createCompoundStatement(Node* localDeclList, Node* statementList)
{
	Node* retNode = createDefaultNode("CompoundStatement", 2);
	retNode->links[0] = localDeclList;
	retNode->links[1] = statementList;
	return retNode;
}

Node* createStatementNode(Node* statementDeclaration)
{
	Node* retNode = createDefaultNode("Statement", 1);
	retNode->links[0] = statementDeclaration;
	return retNode;
}

Node* createExpressionStatement(Node* expressionDeclaration)
{
	Node* retNode = createDefaultNode("ExpressionStatement", 1);
	retNode->links[0] = expressionDeclaration;
	return retNode;
}

Node* createReturnStatement(Node* expressionDeclaration)
{
	Node* retNode = createDefaultNode("ReturnStatement", 1);
	retNode->links[0] = expressionDeclaration;
	return retNode;
}

Node* createExpressionNode(Node* expressionDeclaration)
{
	Node* retNode = createDefaultNode("Expression", 1);
	retNode->links[0] = expressionDeclaration;
	return retNode;
}

Node* createParametersDeclarationNode(Node* parametersDeclaration)
{
	Node* retNode = createDefaultNode("Parameters", 1);
	retNode->links[0] = parametersDeclaration;
	return retNode;
}

Node* newSimpExp(Node* addExp1, Node* relop, Node* addExp2)
{
	Node* retNode = createDefaultNode("SimpleExpression", 3);
	retNode->links[0] = addExp1;
	retNode->links[1] = relop;
	retNode->links[2] = addExp2;

	return retNode;
}

Node* newAddExp(Node* addExp, Node* addop, Node* term)
{
	Node* retNode = createDefaultNode("AdditiveExpression", 3);
	retNode->links[0] = addExp;
	retNode->links[1] = addop;
	retNode->links[2] = term;

	return retNode;
}

Node* newTerm(Node* term, Node* mulop, Node* factor)
{
	Node* retNode = createDefaultNode("Term", 3);
	retNode->links[0] = term;
	retNode->links[1] = mulop;
	retNode->links[2] = factor;

	return retNode;
}

Node* newCall(char* ID, Node* args)
{
	Node* retNode = createDefaultNode("Call", 1);
	retNode->links[0] = args;
	if (ID)
		sprintf(retNode->extraData, "%s", ID);

	return retNode;
}

Node* newArgList(Node* argList)
{
	Node* retNode = createDefaultNode("Arguments", 1);
	retNode->links[0] = argList;

	return retNode;
}

Node* newNumNode(Node* expression, int val)
{
	Node* retNode = createDefaultNode("Factor", 1);
	if (expression)
		retNode->links[0] = expression;
	else if (val != 0)
	{
		retNode->links[0] = createDefaultNode("Num", 0);
		sprintf(retNode->links[0]->extraData, "%d", val);
	}

	return retNode;
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