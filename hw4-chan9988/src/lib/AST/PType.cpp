#include "AST/PType.hpp"

#include <typeinfo>
#include <cstring>


const char *kTypeString[] = {"void", "integer", "real", "boolean", "string"};

PType::PType(PrimitiveTypeEnum type) : type(type) {}

void PType::setDimensions(std::vector<uint64_t> &dims) {
    dimensions = std::move(dims);
}

const PType::PrimitiveTypeEnum PType::getPrimitiveType() const { return type; }

// logical constness
const char *PType::getPTypeCString() const {
    if (!type_string_is_valid) {
        type_string += kTypeString[static_cast<int>(type)];

        if (dimensions.size() != 0) {
            type_string += " ";

            for (const auto &dim : dimensions) {
                type_string += "[" + std::to_string(dim) + "]";
            }
        }
        type_string_is_valid = true;
    }

    return type_string.c_str();
}

bool PType::check_ptype() const {
	bool ch=false;
	for (const auto &dim : dimensions) {
                if(dim<=0) ch=true;
            }
	return ch;
}

int PType::ptype_num() const {
	return dimensions.size();
}

//bool PType::check_ptype_is_int() const {
//	bool ch=true;
//	for (const auto &dim : dimensions) {
//                if(strcmp(typeid(dim).name(),"i")==0) ch=false;
//            }
//	return ch;
//}
