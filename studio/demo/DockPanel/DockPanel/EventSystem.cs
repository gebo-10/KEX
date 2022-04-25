using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
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
        public Type type;
        public Vector2 position;
        public int button;
    }
    public class EventSystem
    {
    }
}
