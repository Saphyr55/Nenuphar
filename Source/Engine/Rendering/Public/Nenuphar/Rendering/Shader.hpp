#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Math/Matrix4.hpp"
#include "Nenuphar/Rendering/UniformTypes.hpp"

namespace Nenuphar
{
    using ShaderId = UInt32;
    using ShaderProgramId = UInt32;

    class UniformRegistry;

    /**
     * @brief 
     * 
     */
    class Shader
    {
    public:
        /**
         * @brief 
         * 
         */
        virtual void Use() const = 0;

        /**
         * @brief 
         * 
         * @return ShaderProgramId 
         */
        virtual ShaderProgramId Id() const = 0;

        /**
         * @brief Get the Uniform Location depending on the name.
         * 
         * @param name 
         * @return UniformLocation 
         */
        virtual UniformLocation GetUniformLocation(std::string_view name) const = 0;

        /**
         * @brief Get the Uniform Updater object
         * 
         * @return UniformUpdater 
         */
        virtual UniformUpdater GetUniformUpdater() const = 0;

        /**
         * @brief Destroy the Shader.
         * 
         */
        virtual ~Shader() = default;
    };

    /**
     * @brief 
     * 
     */
    struct MainUniformBlock
    {
        Matrix4f Projection;
        Matrix4f View;
    };

    /**
     * @brief 
     * 
     */
    class MainShaderProgram
    {
    public:
        /**
         * @brief Get the Delegate object
         * 
         * @return SharedRef<Shader> 
         */
        virtual SharedRef<Shader> GetDelegate() = 0;

        /**
         * @brief 
         * 
         * @return const MainUniformBlock& 
         */
        virtual const MainUniformBlock& UMainUniformBlock() const = 0;

        /**
         * @brief Get the Registry object
         * 
         * @return SharedRef<UniformRegistry> 
         */
        virtual SharedRef<UniformRegistry> GetRegistry() = 0;

        /**
         * @brief 
         * 
         * @param mainUniformBlock 
         */
        virtual void UpdateBlock(const MainUniformBlock& mainUniformBlock) = 0;

        /**
         * @brief 
         * 
         * @param projection 
         */
        virtual void UpdateProjection(const Matrix4f& projection) = 0;

        /**
         * @brief 
         * 
         * @param view 
         */
        virtual void UpdateView(const Matrix4f& view) = 0;

    };

}// namespace Nenuphar