// csc /platform:x86 /out:Debug\Managed.exe Managed.cs

using System.Runtime.InteropServices;

[Guid("35B60A55-8F41-4231-BA7F-10EFB95CEBC9")]
[InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
interface IHen
{
    [PreserveSig] void Cluck();
    [PreserveSig] void Roost();
}

[Guid("CCCB9EAF-6856-4D0D-A8A4-048FDCDEB6D8")]
[InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
interface IHen2
{
    // IHen
    [PreserveSig] void Cluck();
    [PreserveSig] void Roost();

    // IHen2
    [PreserveSig] void Forage();
}

class Application
{
    static void Main()
    {
        IHen hen = CreateHen();
        hen.Cluck();
        hen.Roost();

        IHen2 hen2 = (IHen2) hen;
        hen2.Forage();
    }

    [DllImport("Library.dll", PreserveSig = false)]
    static extern IHen CreateHen();
}