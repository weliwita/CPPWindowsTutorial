using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.ApplicationModel.Core;
using Windows.UI.Core;

namespace App1
{
    class App: IFrameworkViewSource, IFrameworkView
    {
        static void Main()
        {
            CoreApplication.Run(new App());
        }

        public IFrameworkView CreateView()
        {
            return this;
        }

        public void Initialize(CoreApplicationView applicationView)
        {
            
        }

        public void Load(string entryPoint)
        {
            
        }

        public void Run()
        {
            CoreWindow window = CoreWindow.GetForCurrentThread();
            window.Activate();

            CoreDispatcher dispatcher = window.Dispatcher;
            dispatcher.ProcessEvents(CoreProcessEventsOption.ProcessUntilQuit);
        }

        public void SetWindow(CoreWindow window)
        {
            
        }

        public void Uninitialize()
        {
           
        }
    }
}
