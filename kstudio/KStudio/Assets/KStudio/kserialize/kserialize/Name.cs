// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace kserialize
{

using global::System;
using global::System.Collections.Generic;
using global::FlatBuffers;

public struct Name : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_2_0_0(); }
  public static Name GetRootAsName(ByteBuffer _bb) { return GetRootAsName(_bb, new Name()); }
  public static Name GetRootAsName(ByteBuffer _bb, Name obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public Name __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint Id { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public string Str { get { int o = __p.__offset(6); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetStrBytes() { return __p.__vector_as_span<byte>(6, 1); }
#else
  public ArraySegment<byte>? GetStrBytes() { return __p.__vector_as_arraysegment(6); }
#endif
  public byte[] GetStrArray() { return __p.__vector_as_array<byte>(6); }

  public static Offset<kserialize.Name> CreateName(FlatBufferBuilder builder,
      uint id = 0,
      StringOffset strOffset = default(StringOffset)) {
    builder.StartTable(2);
    Name.AddStr(builder, strOffset);
    Name.AddId(builder, id);
    return Name.EndName(builder);
  }

  public static void StartName(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddId(FlatBufferBuilder builder, uint id) { builder.AddUint(0, id, 0); }
  public static void AddStr(FlatBufferBuilder builder, StringOffset strOffset) { builder.AddOffset(1, strOffset.Value, 0); }
  public static Offset<kserialize.Name> EndName(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<kserialize.Name>(o);
  }
  public NameT UnPack() {
    var _o = new NameT();
    this.UnPackTo(_o);
    return _o;
  }
  public void UnPackTo(NameT _o) {
    _o.Id = this.Id;
    _o.Str = this.Str;
  }
  public static Offset<kserialize.Name> Pack(FlatBufferBuilder builder, NameT _o) {
    if (_o == null) return default(Offset<kserialize.Name>);
    var _str = _o.Str == null ? default(StringOffset) : builder.CreateString(_o.Str);
    return CreateName(
      builder,
      _o.Id,
      _str);
  }
};

public class NameT
{
  public uint Id { get; set; }
  public string Str { get; set; }

  public NameT() {
    this.Id = 0;
    this.Str = null;
  }
}


}
