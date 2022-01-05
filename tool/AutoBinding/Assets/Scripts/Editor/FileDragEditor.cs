using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using AutoMetaData;
[CustomEditor(typeof(FileListConfig))]  //����Test��ԭ���ű�������
public class EditTest : Editor   //�̳и�ΪEditor
{
    FileListConfig config; //�ű�����
    SerializedObject serObj;//������ȡ���ű�����
    SerializedProperty files;

    Rect rect;
    /// <summary>
    /// ��ʼ�� Objcet���󣬰󶨸������� ץȡ�ű����������
    /// </summary>
    private void OnEnable()
    {
        config = (FileListConfig)target;
        serObj = new SerializedObject(target);

        files = serObj.FindProperty("files");

    }

    /// <summary>
    /// ��ʾ
    /// </summary>
    public override void OnInspectorGUI() //���½ű�����Ϣ
    {
        serObj.Update();
        EditorGUILayout.LabelField("�϶�ͷ�ļ�������", EditorStyles.label);
        rect = EditorGUILayout.GetControlRect(GUILayout.Width(400), GUILayout.Height(50));

        EditorGUILayout.Separator();
        EditorGUILayout.PropertyField(files, new GUIContent("files"));

        if ((Event.current.type == EventType.DragUpdated ||
            Event.current.type == EventType.DragExited) &&
        rect.Contains(Event.current.mousePosition))
        {
            DragAndDrop.visualMode = DragAndDropVisualMode.Generic;
            if (DragAndDrop.paths != null && DragAndDrop.paths.Length > 0)
            {
                string path = DragAndDrop.paths[0];
                //path=path.Substring(23);
                if (!config.files.Contains(path))
                {
                    config.files.Add(path);
                }
            }
        }


        serObj.ApplyModifiedProperties(); //���ͨ����Ӧ���޸�����Ч�� 
    }
}