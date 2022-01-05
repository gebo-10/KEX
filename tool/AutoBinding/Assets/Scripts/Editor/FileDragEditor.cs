using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using AutoMetaData;
[CustomEditor(typeof(FileListConfig))]  //这里Test是原来脚本的名字
public class EditTest : Editor   //继承改为Editor
{
    FileListConfig config; //脚本本体
    SerializedObject serObj;//用来获取各脚本变量
    SerializedProperty files;

    Rect rect;
    /// <summary>
    /// 初始化 Objcet对象，绑定各变量， 抓取脚本里面的属性
    /// </summary>
    private void OnEnable()
    {
        config = (FileListConfig)target;
        serObj = new SerializedObject(target);

        files = serObj.FindProperty("files");

    }

    /// <summary>
    /// 显示
    /// </summary>
    public override void OnInspectorGUI() //更新脚本的信息
    {
        serObj.Update();
        EditorGUILayout.LabelField("拖动头文件到下面", EditorStyles.label);
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


        serObj.ApplyModifiedProperties(); //最后，通过此应用修改属性效果 
    }
}