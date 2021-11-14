using UnityEditor;
using UnityEngine;

[CustomEditor(typeof(MyData), true)]
[CanEditMultipleObjects]
public class BaseDataEditor : Editor
{
    //序列化对象
    private SerializedObject obj;
    MyData m_OrginData;
    //学历恶化属性
    private SerializedProperty MyPath;

    Rect mPathRect;

    private void OnEnable()
    {
        obj = new SerializedObject(target);

        MyPath = obj.FindProperty("m_myPath");

        m_OrginData = (MyData)target;
    }

    public override void OnInspectorGUI()
    {
        EditorGUILayout.PropertyField(MyPath);

        //获得一个长500的框  
        mPathRect = EditorGUILayout.GetControlRect(GUILayout.Width(500));
        //如果鼠标正在拖拽中或拖拽结束时，并且鼠标所在位置在文本输入框内  
        if ((Event.current.type == EventType.DragUpdated || Event.current.type == EventType.DragExited) && mPathRect.Contains(Event.current.mousePosition))
        {
            //改变鼠标的外表  
            DragAndDrop.visualMode = DragAndDropVisualMode.Generic;
            if (DragAndDrop.paths != null && DragAndDrop.paths.Length > 0)
            {
                string retPath = DragAndDrop.paths[0];
                MyPath.stringValue = retPath;
                m_OrginData.SetPdfPath(retPath);
            }
            obj.ApplyModifiedProperties();
            obj.Update();
        }
    }
}