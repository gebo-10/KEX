using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KUI
{
    public class Event
    {
        //public int Id { get; set; }
        public enum Type
        {
            PointMove,
            PointIn,
            PointLeave,
            PointDown,
            PointUp,
            PointClick,
        }
        public enum PointAction
        {
            Release,
            Press,
            Repeat,
        }
        public Type type;
        public float x;
        public float y;
        public int button;
        public PointAction action;
    }
    public class EventSystem
    {
    }
}
