#include "AST/ConstantValue.hpp"

// TODO
ConstantValueNode::ConstantValueNode(const uint32_t line, const uint32_t col,int type,int intconstant,double doubleconstant,const char *str): ExpressionNode{line, col},type(type),intconstant(intconstant),doubleconstant(doubleconstant),str(str) {
	//if(str!=NULL) printf("%s\n",str);
}

// TODO: You may use code snippets in AstDumper.cpp
void ConstantValueNode::print() {
	tab++;
	int t=tab;
	while(t--){
		printf("  ");
	}
	if(type==0){
		printf("constant <line: %u, col: %u> %d\n",location.line,location.col,intconstant);
	
	}
	else if(type==1){
		printf("constant <line: %u, col: %u> %f\n",location.line,location.col,doubleconstant);
	
	}
	else if(type==2||type==3){
		printf("constant <line: %u, col: %u> %s\n",location.line,location.col,str);
	}
	tab--;
}
