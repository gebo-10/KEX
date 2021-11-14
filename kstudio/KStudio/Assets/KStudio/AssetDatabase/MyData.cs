using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MyData : MonoBehaviour
{
    [SerializeField]
    public string m_myPath;

    public string GetPdfPath()
    {
        return m_myPath;
    }
    public void SetPdfPath(string path)
    {
        m_myPath = path;
    }
}