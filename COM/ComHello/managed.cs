using System.Runtime.InteropServices;

class Application
{
    static void Main()
    {
        Cluck();

    }

    [DllImport("Library.dll")]
    static extern void Cluck();
}