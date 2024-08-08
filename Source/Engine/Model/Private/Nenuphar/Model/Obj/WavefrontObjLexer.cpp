#include "WavefrontObjLexer.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"

#include <cctype>
#include <sstream>

namespace Nenuphar
{
    using InputStream = std::istringstream;

    std::unordered_map<const char*, WavefrontObjToken::Type> WavefrontObjLexer::Keywords
    {
        {"v", WavefrontObjToken::Type::V},
        {"vt", WavefrontObjToken::Type::VT},
        {"vp", WavefrontObjToken::Type::VP},
        {"vn", WavefrontObjToken::Type::VN},
        {"def", WavefrontObjToken::Type::Deg},
        {"bmat", WavefrontObjToken::Type::BMatrix},
        {"step", WavefrontObjToken::Type::Step},
        {"cstype", WavefrontObjToken::Type::CSType},
        {"p", WavefrontObjToken::Type::Point},
        {"l", WavefrontObjToken::Type::Line},
        {"f", WavefrontObjToken::Type::Face},
        {"curv", WavefrontObjToken::Type::Curve},
        {"curv2", WavefrontObjToken::Type::Curve2D},
        {"surf", WavefrontObjToken::Type::Surface},
        {"parm", WavefrontObjToken::Type::Param},
        {"trim", WavefrontObjToken::Type::Trim},
        {"scrv", WavefrontObjToken::Type::SCRV},
        {"sp", WavefrontObjToken::Type::SP},
        {"end", WavefrontObjToken::Type::End},
        {"vn", WavefrontObjToken::Type::VN},
        {"con", WavefrontObjToken::Type::Connect},
        {"g", WavefrontObjToken::Type::Group},
        {"sg", WavefrontObjToken::Type::SGroup},
        {"mg", WavefrontObjToken::Type::MGroup},
        {"o", WavefrontObjToken::Type::Object},
        {"bevel", WavefrontObjToken::Type::Bevel},
        {"c_interp", WavefrontObjToken::Type::C_interp},
        {"d_interp", WavefrontObjToken::Type::D_interp},
        {"lod", WavefrontObjToken::Type::LoD},
        {"usemlt", WavefrontObjToken::Type::USEMLT},
        {"mtllib", WavefrontObjToken::Type::MaterialLib},
        {"shadow_obj", WavefrontObjToken::Type::ShadowObj},
        {"trace_obj", WavefrontObjToken::Type::TraceObj},
        {"ctech", WavefrontObjToken::Type::Ctech},
        {"stech", WavefrontObjToken::Type::Stech},
    };

    WavefrontObjLexer::WavefrontObjLexer(StringView source)
            : m_source(source)
    {

    }

    void WavefrontObjLexer::Report(StringView msg)
    {
        NP_ERROR(WavefrontObjLexer::Report, "{}", msg);
    }

    void WavefrontObjLexer::AddToken(StringView text, WavefrontObjToken::Type kind)
    {
        m_tokens.push_back(WavefrontObjToken(String(text), kind));
    }

    void WavefrontObjLexer::AddToken(WavefrontObjToken::Type kind)
    {
        String subText = m_source.substr(m_start, m_position);
        AddToken(subText, kind);
    }

    void WavefrontObjLexer::AddDefaultToken(const char& current)
    {
        if (std::isalpha(current))
        {
            AddIdentifierToken();
        }
        else if (std::isdigit(current))
        {
            AddNumberToken();
        }

        Report("Unexpected character.");
    }

    void WavefrontObjLexer::AddIdentifierToken()
    {
        while (std::isalnum(Peek()))
        {
            GetPosAndNext();
        }

        String text = m_source.substr(m_start, m_position);
        WavefrontObjToken::Type kind = WavefrontObjToken::Type::Identifier;

        if (Keywords.contains(text.c_str()))
        {
            kind = Keywords.at(text.c_str());
        }

        AddToken(text, kind);
    }

    void WavefrontObjLexer::AddNumberToken()
    {
        
    }

    std::vector<WavefrontObjToken> WavefrontObjLexer::Scan()
    {
        while (!IsAtEnd())
        {
            m_start = m_position;
            NextToken();
        }

        m_tokens.push_back(WavefrontObjToken("\0", WavefrontObjToken::Type::Eof));

        return m_tokens;
    }

    void WavefrontObjLexer::SkipComment()
    {
        while (Peek() == '\n');
    }

    Void WavefrontObjLexer::NextToken()
    {
        const char& current = GetAndAdvance();
        switch (current)
        {
        case '#':
            SkipComment();
            break;
        case '/':
            AddToken(WavefrontObjToken::Type::Slash);
            break;
        case '-':
            AddToken(WavefrontObjToken::Type::Neg);
            break;
        case '.':
            AddToken(WavefrontObjToken::Type::Dot);
            break;
        case '\n':
            AddToken(WavefrontObjToken::Type::NewLine);
            break;
        default:
            AddDefaultToken(current);
            break;
        }
    }

    Char WavefrontObjLexer::Peek()
    {
        return IsAtEnd() ? '\0' : m_source.at(m_position);
    }

    Char WavefrontObjLexer::GetAndAdvance()
    {
        return m_source.at(GetPosAndNext());
    }

    Int WavefrontObjLexer::GetPosAndNext()
    {
        m_col++;
        return m_position++;
    }

    bool WavefrontObjLexer::IsAtEnd()
    {
        return m_position >= m_source.length();
    }

    bool WavefrontObjLexer::MatchWith(const char& c)
    {
        if (IsAtEnd())
        {
            return false;
        }

        if (Peek() == c)
        {
            GetPosAndNext();
            return true;
        }

        return false;
    }
}