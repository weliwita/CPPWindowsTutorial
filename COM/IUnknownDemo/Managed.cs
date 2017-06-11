// csc /platform:x86 /out:Debug\Managed.exe Managed.cs

using System.Runtime.InteropServices;

[Guid("7fa1fd7e-ac45-4b2e-acd9-0cd824417adb")]
[InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
interface IHen
{
    [PreserveSig] void Cluck();
    [PreserveSig] void Roost();
}

[Guid("c712d745-c0a8-45be-bcec-7815112dd8f7")]
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