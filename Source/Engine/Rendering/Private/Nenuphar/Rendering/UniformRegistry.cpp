#include "Nenuphar/Rendering/UniformRegistry.hpp"

namespace Nenuphar
{

    UniformRegistry::UniformRegistry(SharedRef<Shader> program)
        : m_owner(program)
    {
    }

    StandardUniform& UniformRegistry::GetStandard(std::string_view name)
    {
        NCHECK(m_registry.contains(name.data()))
        StandardUniform& uniform = m_registry.at(name.data());
        return uniform;
    }

    SharedRef<Shader> UniformRegistry::Owner()
    {
        return m_owner;
    }

}// namespace Nenuphar