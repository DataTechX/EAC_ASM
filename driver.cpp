char EAC::Callbacks::SomeDriverChecks()
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  pOutputResult = 0; // [rsp+0h] [rbp-108h]
  v14 = -5772; // [rsp+8h] [rbp-100h]
  pCheckDriverDispatch = 0; // check driver dispatch
  v13[0] = -683422989; // [rsp+10h] [rbp-F8h]
  v15[0] = 0i64;
  v1 = 0i64;
  LOWORD(v15[1]) = 0;
  v2 = -685061481;
  v13[1] = -2105495067;
  v21 = v13;
  v22 = v15;
  v3 = 8i64;
  do
  {
    *(v22 + v1 * 4) = v21[v1] ^ v2;
    ++v1;
    v2 = __ROL4__(((v2 ^ (v2 << 13)) >> 17) ^ v2 ^ (v2 << 13) ^ (32 * (((v2 ^ (v2 << 13)) >> 17) ^ v2 ^ (v2 << 13))), 1);
  }
  while ( v1 < 2 );
  v21 = v13;
  v22 = v15;
  do
  {
    v4 = v2;
    v2 >>= 8;
    *(v22 + v3) = *(v21 + v3) ^ v4;
    ++v3;
  }
  while ( v3 < 0xA );
  EAC::Memory::memset(&nDriverCTLMinusAddress, 0, 0x108ui64); // สร้าง buffer ขนาด 0x108 ไว้เก็บข้อมูล
  EAC::Memory::InitializeUnicodeStringWithCString(v16, v15); // สร้าง unicode string จาก string ที่เก็บไว้ใน v15
  pDriverObject = EAC::Memory::GetDriverObject(v16);
  pDriverObject_1 = pDriverObject;
  if ( pDriverObject )
  {
    pCheckDriverDispatch = EAC::Callbacks::CheckDriverDispatch(
                             pDriverObject,
                             v6,
                             &nDriverCTLMinusAddress,
                             &pOutputResult);
    ObfDereferenceObject(pDriverObject_1);
    nDetectionResult = pOutputResult;
  }
  else
  {
    nDetectionResult = 1;
  }
  for ( i = 0i64; i < 256; ++i )
  {
    if ( !a3_8[i] )
      break;
  }
  pAllocated = EAC::Memory::ExAllocatePoolWithRandomTag2(i + 0xA);
  pAllocated_1 = pAllocated;
  if ( pAllocated )                             // send driver information to server aswell?
  {
    EAC::Memory::memset(pAllocated, 0, i + 0xA);
    pAllocated_1->nDriverCTLMinusAddress = nDriverCTLMinusAddress;
    pAllocated_1->dword5 = a3_4;
    pAllocated_1->nDetectionResult = nDetectionResult;
    if ( i )
      EAC::Memory::memmove(&pAllocated_1->oword9, a3_8, i);
    if ( i != 0xFFFFFFFFFFFFFFF6ui64 )
    {
      EAC::Callbacks::ReportViolation(0x125F58F6i64, pAllocated_1, (i + 0xA));
FREE_POOL_LABEL:
      EAC::Memory::ExFreePool(pAllocated_1);
      goto END_RET_LABEL;
    }
  }
  EAC::Callbacks::ReportViolation(0x125F58F6i64, 0i64, 0i64);
  if ( pAllocated_1 )
    goto FREE_POOL_LABEL;
END_RET_LABEL:
  memset(v15, 0, 0xAui64);
  return pCheckDriverDispatch;
}