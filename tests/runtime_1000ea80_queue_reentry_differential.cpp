#include <Windows.h>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

extern std::uint32_t __stdcall FUN_1000ea80();
std::int32_t DAT_1003c3b8 = 0;

namespace {
constexpr std::uint32_t kBase = 0x10000000;
constexpr std::uint32_t kAddress = 0x1000ea80;
constexpr char kOriginal[] = "C:\\Users\\caner\\OneDrive\\Documents\\ImVehFt\\ImVehFt.asi";
using Callback = void (__cdecl*)();
using ReturnCallback = std::uint32_t (__cdecl*)();
struct Observation { std::vector<std::uint32_t> events; std::uint32_t result = 0; };
Observation* active = nullptr;
std::uint32_t g_mode = 0;
std::uint32_t g_nested = 0;
std::uint32_t* g_second_end = nullptr;
std::uint32_t* g_second_extra = nullptr;
std::uint32_t g_dispatch = 0;
std::uint8_t manager[0x30]{};
std::uint32_t first[3]{};
std::uint32_t second[3]{};

std::uint8_t* MapOriginal()
{
    HANDLE f=CreateFileA(kOriginal,GENERIC_READ,FILE_SHARE_READ,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr);
    if(f==INVALID_HANDLE_VALUE)return nullptr;
    DWORD size=GetFileSize(f,nullptr);if(size==INVALID_FILE_SIZE){CloseHandle(f);return nullptr;}
    std::vector<std::uint8_t> bytes(size);DWORD read=0;BOOL ok=ReadFile(f,bytes.data(),size,&read,nullptr);CloseHandle(f);
    if(!ok||read!=size)return nullptr;
    auto const* dos=reinterpret_cast<IMAGE_DOS_HEADER const*>(bytes.data());
    if(dos->e_magic!=IMAGE_DOS_SIGNATURE||dos->e_lfanew<0)return nullptr;
    auto const* nt=reinterpret_cast<IMAGE_NT_HEADERS32 const*>(bytes.data()+dos->e_lfanew);
    if(nt->Signature!=IMAGE_NT_SIGNATURE||nt->FileHeader.Machine!=IMAGE_FILE_MACHINE_I386||nt->OptionalHeader.ImageBase!=kBase)return nullptr;
    auto* image=static_cast<std::uint8_t*>(VirtualAlloc(reinterpret_cast<void*>(kBase),nt->OptionalHeader.SizeOfImage,MEM_RESERVE|MEM_COMMIT,PAGE_EXECUTE_READWRITE));
    if(image!=reinterpret_cast<std::uint8_t*>(kBase))return nullptr;
    std::memset(image,0,nt->OptionalHeader.SizeOfImage);std::memcpy(image,bytes.data(),nt->OptionalHeader.SizeOfHeaders);
    auto const* sec=IMAGE_FIRST_SECTION(nt);
    for(unsigned i=0;i<nt->FileHeader.NumberOfSections;++i,++sec){if(!sec->SizeOfRawData)continue;
        if(sec->PointerToRawData>bytes.size()||sec->SizeOfRawData>bytes.size()-sec->PointerToRawData||sec->VirtualAddress>nt->OptionalHeader.SizeOfImage||sec->SizeOfRawData>nt->OptionalHeader.SizeOfImage-sec->VirtualAddress){VirtualFree(image,0,MEM_RELEASE);return nullptr;}
        std::memcpy(image+sec->VirtualAddress,bytes.data()+sec->PointerToRawData,sec->SizeOfRawData);}
    return image;
}
void Put(std::uint32_t offset, std::uint32_t value){std::memcpy(manager+offset,&value,4);}
std::uint32_t Ptr(const void* p){return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(p));}
void Record(std::uint32_t id){active->events.push_back(id);}
extern "C" void __cdecl A(){Record(1);if(g_mode==3&&!g_nested){g_nested=1;if(g_dispatch==1)FUN_1000ea80();else reinterpret_cast<std::uint32_t(__cdecl*)()>(kBase+(kAddress-kBase))();}}
extern "C" void __cdecl B(){Record(2);}
extern "C" void __cdecl C(){Record(3);}
extern "C" void __cdecl D(){Record(4);}
extern "C" std::uint32_t __cdecl Middle(){Record(5);if(g_mode==2&&g_second_extra){*g_second_end=Ptr(g_second_extra+1);}return 0xfeed1234U;}

void Setup(std::uint32_t mode)
{
    std::memset(manager,0,sizeof(manager));std::memset(first,0,sizeof(first));std::memset(second,0,sizeof(second));
    g_mode=mode;g_nested=0;g_second_extra=(mode==2)?&second[1]:nullptr;g_second_end=reinterpret_cast<std::uint32_t*>(manager+0x2c);
    if(mode==1){first[0]=Ptr(&A);first[1]=0;first[2]=Ptr(&B);second[0]=Ptr(&C);second[1]=Ptr(&D);Put(0x18,Ptr(first));Put(0x1c,Ptr(first+3));Put(0x28,Ptr(second));Put(0x2c,Ptr(second+2));}
    else if(mode==2){first[0]=Ptr(&A);Put(0x18,Ptr(first));Put(0x1c,Ptr(first+1));second[0]=Ptr(&C);second[1]=Ptr(&D);Put(0x28,Ptr(second));Put(0x2c,Ptr(second+1));}
    else {first[0]=Ptr(&A);first[1]=Ptr(&B);second[0]=Ptr(&C);Put(0x18,Ptr(first));Put(0x1c,Ptr(first+2));Put(0x28,Ptr(second));Put(0x2c,Ptr(second+1));}
    Put(0x10,Ptr(&Middle));
}
Observation Run(Callback function,std::uint32_t mode,std::uint32_t dispatch){Observation o{};active=&o;g_dispatch=dispatch;Setup(mode);o.result=reinterpret_cast<ReturnCallback>(function)();active=nullptr;return o;}
bool Equal(Observation const&a,Observation const&b){return a.result==b.result&&a.events==b.events;}
}

int main()
{
    auto* image=MapOriginal();if(!image){std::fprintf(stderr,"failed to map original ASI\n");return 2;}
    auto* manager_slot=reinterpret_cast<std::uint32_t*>(image+(0x1003c3b8U-kBase));
    using Handler=std::uint32_t(__stdcall*)();auto original=reinterpret_cast<Handler>(image+(kAddress-kBase));
    Callback candidate=reinterpret_cast<Callback>(&FUN_1000ea80);
    for(std::uint32_t mode=1;mode<=3;++mode){
        Setup(mode);*manager_slot=Ptr(manager);auto ref=Run(reinterpret_cast<Callback>(original),mode,0);
        Setup(mode);DAT_1003c3b8=static_cast<std::int32_t>(Ptr(manager));auto cand=Run(candidate,mode,1);
        if(!Equal(ref,cand)){std::fprintf(stderr,"mode %u mismatch result %08x/%08x event-count %zu/%zu\n",mode,ref.result,cand.result,ref.events.size(),cand.events.size());return static_cast<int>(10+mode);}
        std::printf("mode %u pass: result=%08x callbacks=%zu\n",mode,ref.result,ref.events.size());
    }
    return 0;
}
