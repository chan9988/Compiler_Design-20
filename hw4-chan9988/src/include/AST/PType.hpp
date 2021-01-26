#ifndef __AST_PTYPE_H
#define __AST_PTYPE_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class PType;

typedef std::shared_ptr<const PType> PTypeSharedPtr;

class PType {
  public:
    enum class PrimitiveTypeEnum : uint8_t {
        kVoidType,
        kIntegerType,
        kRealType,
        kBoolType,
        kStringType
    };

    PType(PrimitiveTypeEnum type);
    ~PType() = default;

	//PType(PrimitiveTypeEnum type,int a) : type(type),dim(a) {}

    void setDimensions(std::vector<uint64_t> &dims);

    const PrimitiveTypeEnum getPrimitiveType() const;
    const char *getPTypeCString() const;

	bool check_ptype() const;
	int ptype_num() const;
	//bool check_ptype_is_int() const;


  private:
    PrimitiveTypeEnum type;
    std::vector<uint64_t> dimensions;
    mutable std::string type_string;
    mutable bool type_string_is_valid = false;
};

#endif
