#include "../../include/enums/ast_enumerator_specifier.hpp"

Type EnumeratorSpecifier::GetType() const
{
    return Type::_INT;
}

void EnumeratorSpecifier::DefineSpecifier(Context &context) const
{
    if (enumerator_list_ != nullptr)
    {
        int enum_value = 0;
        std::vector<std::string> labels;

        for (auto node_ : enumerator_list_->get_nodes())
        {
            Enumerator *enumerator_ = dynamic_cast<Enumerator *>(node_);
            enum_value = enumerator_->DefineEnumerator(context, enum_value);
            labels.push_back(enumerator_->GetLabel());
        }

        context.define_enum(*identifier_, labels);
    }
}

void EnumeratorSpecifier::Print(std::ostream &stream) const
{
    stream << "enum ";

    if (identifier_)
    {
        stream << *identifier_;
    }

    if (enumerator_list_)
    {
        stream << "{";
        enumerator_list_->Print(stream);
        stream << "}";
    }
}
