// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace kserialize
{

using global::System;
using global::System.Collections.Generic;
using global::FlatBuffers;

public struct AssetBundle : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_2_0_0(); }
  public static AssetBundle GetRootAsAssetBundle(ByteBuffer _bb) { return GetRootAsAssetBundle(_bb, new AssetBundle()); }
  public static AssetBundle GetRootAsAssetBundle(ByteBuffer _bb, AssetBundle obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public AssetBundle __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint Id { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public kserialize.AssetInfo? AssetInfos(int j) { int o = __p.__offset(6); return o != 0 ? (kserialize.AssetInfo?)(new kserialize.AssetInfo()).__assign(__p.__indirect(__p.__vector(o) + j * 4), __p.bb) : null; }
  public int AssetInfosLength { get { int o = __p.__offset(6); return o != 0 ? __p.__vector_len(o) : 0; } }

  public static Offset<kserialize.AssetBundle> CreateAssetBundle(FlatBufferBuilder builder,
      uint id = 0,
      VectorOffset asset_infosOffset = default(VectorOffset)) {
    builder.StartTable(2);
    AssetBundle.AddAssetInfos(builder, asset_infosOffset);
    AssetBundle.AddId(builder, id);
    return AssetBundle.EndAssetBundle(builder);
  }

  public static void StartAssetBundle(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddId(FlatBufferBuilder builder, uint id) { builder.AddUint(0, id, 0); }
  public static void AddAssetInfos(FlatBufferBuilder builder, VectorOffset assetInfosOffset) { builder.AddOffset(1, assetInfosOffset.Value, 0); }
  public static VectorOffset CreateAssetInfosVector(FlatBufferBuilder builder, Offset<kserialize.AssetInfo>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static VectorOffset CreateAssetInfosVectorBlock(FlatBufferBuilder builder, Offset<kserialize.AssetInfo>[] data) { builder.StartVector(4, data.Length, 4); builder.Add(data); return builder.EndVector(); }
  public static void StartAssetInfosVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static Offset<kserialize.AssetBundle> EndAssetBundle(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<kserialize.AssetBundle>(o);
  }
  public static void FinishAssetBundleBuffer(FlatBufferBuilder builder, Offset<kserialize.AssetBundle> offset) { builder.Finish(offset.Value); }
  public static void FinishSizePrefixedAssetBundleBuffer(FlatBufferBuilder builder, Offset<kserialize.AssetBundle> offset) { builder.FinishSizePrefixed(offset.Value); }
  public AssetBundleT UnPack() {
    var _o = new AssetBundleT();
    this.UnPackTo(_o);
    return _o;
  }
  public void UnPackTo(AssetBundleT _o) {
    _o.Id = this.Id;
    _o.AssetInfos = new List<kserialize.AssetInfoT>();
    for (var _j = 0; _j < this.AssetInfosLength; ++_j) {_o.AssetInfos.Add(this.AssetInfos(_j).HasValue ? this.AssetInfos(_j).Value.UnPack() : null);}
  }
  public static Offset<kserialize.AssetBundle> Pack(FlatBufferBuilder builder, AssetBundleT _o) {
    if (_o == null) return default(Offset<kserialize.AssetBundle>);
    var _asset_infos = default(VectorOffset);
    if (_o.AssetInfos != null) {
      var __asset_infos = new Offset<kserialize.AssetInfo>[_o.AssetInfos.Count];
      for (var _j = 0; _j < __asset_infos.Length; ++_j) { __asset_infos[_j] = kserialize.AssetInfo.Pack(builder, _o.AssetInfos[_j]); }
      _asset_infos = CreateAssetInfosVector(builder, __asset_infos);
    }
    return CreateAssetBundle(
      builder,
      _o.Id,
      _asset_infos);
  }
};

public class AssetBundleT
{
  public uint Id { get; set; }
  public List<kserialize.AssetInfoT> AssetInfos { get; set; }

  public AssetBundleT() {
    this.Id = 0;
    this.AssetInfos = null;
  }
  public static AssetBundleT DeserializeFromBinary(byte[] fbBuffer) {
    return AssetBundle.GetRootAsAssetBundle(new ByteBuffer(fbBuffer)).UnPack();
  }
  public byte[] SerializeToBinary() {
    var fbb = new FlatBufferBuilder(0x10000);
    AssetBundle.FinishAssetBundleBuffer(fbb, AssetBundle.Pack(fbb, this));
    return fbb.DataBuffer.ToSizedArray();
  }
}


}
