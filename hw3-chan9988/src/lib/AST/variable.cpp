#include "AST/variable.hpp"

// TODO
VariableNode::VariableNode(const uint32_t line, const uint32_t col,char *name,int type,std::vector<int> *arr,int intconstant,double doubleconstant,char *str): AstNode{line, col},name(name),type(type),arr(arr),intconstant(intconstant),doubleconstant(doubleconstant),str(str) {}

// TODO: You may use code snippets in AstDumper.cpp
void VariableNode::print() {
	tab++;
	int t=tab;
	while(t--){
		printf("  ");
	}	
	printf("variable <line: %u, col: %u> %s ",location.line,location.col,name);
	if(type==0) printf("integer ");
	else if(type==1) printf("real ");
	else if(type==2) printf("string ");
	else if(type==3) printf("boolean ");
	if(arr!=NULL){
		for(auto i: *(arr)){
			printf("[%d]",i);		
		}
	}
	printf("\n");
	if(ch!=NULL){
	    ch->print();
	}
	tab--;
}

void VariableNode::add_child(AstNode *n){
    ch=n;
}

// void VariableNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
