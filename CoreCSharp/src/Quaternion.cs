using System;

namespace Xnor.Core
{
    public struct Quaternion
    {
        public static readonly Vector4 Zero = new();
        
        public static readonly Vector4 UnitX = new(1f, 0f, 0f, 0f);
        
        public static readonly Vector4 UnitY = new(0f, 1f, 0f, 0f);
        
        public static readonly Vector4 UnitZ = new(0f, 0f, 1f, 0f);
        
        public static readonly Vector4 UnitW = new(0f, 0f, 0f, 1f);
        
        public static readonly Vector4 Identity = UnitW;
        
        public static readonly Vector4 One = new(1f);
        
        public static Quaternion operator+(Quaternion a, Quaternion b) => new(a.Imaginary + b.Imaginary, a.Real + b.Real);

        public static Quaternion operator-(Quaternion m) => new(-m.Imaginary, -m.Real);

        public static Quaternion operator-(Quaternion a, Quaternion b) => a + -b;

        public static Quaternion operator*(Quaternion a, float scalar) => new(a.Imaginary * scalar, a.Real * scalar);

        public static Quaternion operator*(float scalar, Quaternion b) => b * scalar;

        public static Quaternion operator*(Quaternion a, Quaternion b) => new(a.Imaginary * b.Imaginary, a.Real * b.Real);

        public static Quaternion operator/(Quaternion a, float scalar) => new(a.Imaginary / scalar, a.Real / scalar);

        public static explicit operator Vector3(Quaternion q) => q.Imaginary;

        public static explicit operator Vector4(Quaternion q) => new(q.X, q.Y, q.Z, q.W);
        
        public Vector3 Imaginary;
        public float Real;
        
        public float X => Imaginary.X;
        public float Y => Imaginary.Y;
        public float Z => Imaginary.Z;
        public float W => Real;

        public Quaternion(Vector3 imaginary, float real)
        {
            Imaginary = imaginary;
            Real = real;
        }

        public Quaternion(float xyzw) : this(new(xyzw), xyzw) { }

        public Quaternion(float x, float y, float z, float w) : this(new(x, y, z), w) { }
    
        public bool Equals(Quaternion other) => Imaginary == other.Imaginary && CoreC.Equals(Real, other.Real);

        public override bool Equals(object obj) => obj is Quaternion other && Equals(other);

        public override int GetHashCode() => HashCode.Combine(Imaginary, Real);

        public static bool operator ==(Quaternion left, Quaternion right) => left.Equals(right);

        public static bool operator !=(Quaternion left, Quaternion right) => !left.Equals(right);
    }
}