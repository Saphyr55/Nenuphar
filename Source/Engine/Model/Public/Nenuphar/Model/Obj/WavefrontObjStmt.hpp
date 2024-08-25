#pragma once


namespace Nenuphar 
{
    
    class WavefrontObjStmt
    {
    public:
        virtual ~WavefrontObjStmt() = default;
    };
    
    class VertexStmt : public WavefrontObjStmt
    {
        
    };

}