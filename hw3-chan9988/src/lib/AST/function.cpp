#include "AST/function.hpp"

// TODO
FunctionNode::FunctionNode(const uint32_t line, const uint32_t col,char *name,int returntype)
    : AstNode{line, col},name(name),returntype(returntype){}

// TODO: You may use code  in AstDumper.cpp
void FunctionNode::print() {
	tab++;
	int t=tab;
	while(t--){
		printf("  ");
	}
	printf("function declaration <line: %u, col: %u> %s ",location.line,location.col,name);
	if(returntype==0) printf("integer");
	else if(returntype==1) printf("real");
	else if(returntype==2) printf("string");
	else if(returntype==3) printf("boolean");
	else if(returntype==4) printf("void");
	printf(" (");
	int state=1;
	int s=1;
	for(int i=0;i<arg.size();i++){		
		if(arg[i]==-1){
			state*=(-1);
			s=1;			
		}
		else{		
			if(state==1){
				if(i!=0) printf(", ");
				if(arg[i]==0) printf("integer");
				else if(arg[i]==1) printf("real");
				else if(arg[i]==2) printf("string");
				else if(arg[i]==3) printf("boolean");
				else if(arg[i]==4) printf("void");
			}		
			else if(state==-1){
				if(s==1){
					s=0;
					printf(" ");				
				}
				printf("[%d]",arg[i]);
			}	
		}	
	}
	printf(")");
	printf("\n");
	if(decl.size()!=0){	
		for(auto i: decl){
			i->print();
		}
	}
	if(ch!=NULL) ch->print();
	tab--;
}


void FunctionNode::add_de(AstNode *n){
	decl.push_back(n);
}

void FunctionNode::add_arg(int n){
	arg.push_back(n);
}

void FunctionNode::add_compoundstatement(AstNode *n){
	ch=n;
}

// void FunctionNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
