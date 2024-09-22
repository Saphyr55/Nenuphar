#include "Nenuphar/Rendering/UniformRegistry.hpp"
#include "Nenuphar/Core/Debug.hpp"

namespace Nenuphar
{

    UniformRegistry::UniformRegistry(SharedRef<Shader> program)
        : m_owner(program)
        , m_registry()
    {
    }

    StandardUniform& UniformRegistry::GetStandard(std::string_view name)
    {
        NCHECK(m_registry.contains(std::string(name.data())))
        StandardUniform& uniform = m_registry.at(std::string(name.data()));
        return uniform;
    }

    SharedRef<Shader> UniformRegistry::Owner()
    {
        return m_owner;
    }

}// namespace Nenuphar