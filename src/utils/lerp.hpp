#pragma once

class Lerp
{
    public:
        Lerp( float lower, float upper, float step );

        void Update();

        void Reset( float value );

        float GetLower() const { return m_lower; }
        float GetUpper() const { return m_upper; }
        float GetStep() const { return m_step; }
        float GetValue() const { return m_current_value; }

    private:
        float m_step;
        float m_lower = 0, m_upper = 0;
        float m_current_value = 0;
};
