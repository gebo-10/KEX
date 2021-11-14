using UnityEditor;
using UnityEngine;

[CustomEditor(typeof(MyData), true)]
[CanEditMultipleObjects]
public class BaseDataEditor : Editor
{
    //���л�����
    private SerializedObject obj;
    MyData m_OrginData;
    //ѧ��������
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

        //���һ����500�Ŀ�  
        mPathRect = EditorGUILayout.GetControlRect(GUILayout.Width(500));
        //������������ק�л���ק����ʱ�������������λ�����ı��������  
        if ((Event.current.type == EventType.DragUpdated || Event.current.type == EventType.DragExited) && mPathRect.Contains(Event.current.mousePosition))
        {
            //�ı��������  
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