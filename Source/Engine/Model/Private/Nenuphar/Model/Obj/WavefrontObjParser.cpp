#include "Nenuphar/Model/Obj/WavefrontObjParser.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"
#include "Nenuphar/Model/Obj/WavefrontObjLexer.hpp"

#include <exception>

namespace Nenuphar
{

    WavefrontObjFile WavefrontObjParser::Parse(std::string_view source) 
    {
        m_tokens = WavefrontObjLexing(source);
        m_position = 0;

        return WavefrontObjFile();      
    }

    UniquePtr<WavefrontObjStmt> WavefrontObjParser::ParseVertex()
    {
        
    }

    const WavefrontObjToken& WavefrontObjParser::Consume(WavefrontObjToken::Type kind, String message)
    {
        if (Check(kind)) 
        {
            return Next();
        }

        NP_ERROR(WavefrontObjParser::Consume, "Error : {}", message);

        // TODO: Better handling error.
        throw std::exception();
    }

    Bool WavefrontObjParser::MatchWith(WavefrontObjToken::Type kind)
    {
        Bool result = Check(kind);
        
        if (result) 
        {
            Next();
        }

        return result;
    }

    Bool WavefrontObjParser::IsAtEnd()
    {
        return 
            Check(WavefrontObjToken::Type::End) || 
            Check(WavefrontObjToken::Type::Eos);
    }

    Bool WavefrontObjParser::Check(WavefrontObjToken::Type kind)
    {
        return Peek().Kind == kind;
    }

    const WavefrontObjToken& WavefrontObjParser::Next()
    {
        if (m_position >= m_tokens.size()) 
        {
            return m_tokens.at(m_tokens.size() - 1);
        }

        const auto& token = Peek();
        m_position++;
        return token;
    }

    const WavefrontObjToken& WavefrontObjParser::Peek()
    {
        return m_tokens.at(m_position);
    }

    WavefrontObjParser::WavefrontObjParser()
    {

    }


}