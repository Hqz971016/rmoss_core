# Fixed Packet(固定长度数据包)说明文档

### 1.简介

* fixed_packet.h/cpp提供了数据包抽象类，封装了数据包与字节流之间的相互转化操作。
* fixed_packet_tool.h/cpp，在依赖通信的设备的情况下，进一步简化通信过程，可直接直接发送与接收数据包，封装底层操作。
* 数据包长度：根据协议，定义数据包为32 Byte定长数据包（长度可变）

### 2.数据包创建及解析（Fixed Packet）

* 数据包抽象类

__数据包创建流程：__

* 新建对象
* 加载数据
* 打包

```c++
FixedPacket packet;//新建对象
float angle=10;
//显式装载数据（建议显式）
packet.loadData<float>(angle,3);//一个参数为数据，第二个数据为数据位置
//隐式装载
packet.loadData(angle,3);
packet.pack();//打包数据
```

__数据包解析流程：__

* 新建对象

* 解包（含包校验）
* 取出数据

```c++
/*******自定义解析数据************/
FixedPacket packet;//新建对象
packet.unPack(buffer,unpack_len)//这一步通常封装起来，第一个参数为要处理的buffer，第二个参数代表buffer的长度（要解析的数据长度）
float angle=0;
packet.unloadData(angle,3);//取出数据（隐式，建议隐式）
```

### 3.数据包传输工具（Fixed Packet Tool）

* 快捷发送与接收FixedPacket.

创建FixedPacketTool

```c++
//需要依赖通信设备，假设已经获得正常工作的通信设备。
CommDevInterface *comm_dev;
//实例化数据包工具，初始化的时候，传入通信设备指针
std::shared_ptr<FixedPacketTool> packet_tool_;
packet_tool_=std::make_shared<FixedPacketTool>(comm_dev);
```

Fixed Packet Tool API

```c++
//发送设备是否打开
bool isOpen();
//数据包收发，收发成功返回0，否则返回其他
int sendPacket(FixedPacket packet);
int recvPacket(FixedPacket &packet);
```

* 利用FixedPacketTool简化了数据传输流程，不需要考虑底层字节数据传输细节。

### 4.数据包发送与接收使用示例

发送数据：

```c++
#数据包
FixedPacket packet;
packet.loadData<unsigned char(protocol_example::Gimbal_Angle_Control,1);
packet.loadData<unsigned char>(0x00,2);
packet.loadData<float>(info->pitch_angle,3);
packet.loadData<float>(info->yaw_angle,7);
packet.pack();
#发送
packet_tool_->sendPacket(packet);
```

接收数据：

```c++
FixedPacket packet;
//recvPacket()为堵塞函数，并已经包含unpack操作，无需再次unpack,即已经完成校验。
while(packet_tool_->recvPacket(packet)==0){
	unsigned char cmd;
	packet.unloadData(cmd,1);
｝
```







