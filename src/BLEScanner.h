//
//  BLEScanner.h
//  BLERx
//
//  Created by Chris Kiefer on 29/11/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

@interface BLEScanner : NSObject <CBCentralManagerDelegate, CBPeripheralDelegate>
{
    CBCentralManager *manager;
    NSMutableArray *dicoveredPeripherals;
    CBPeripheral *testPeripheral;
    BOOL connected;
}
@property (nonatomic, retain) NSData * value;

-(id) init;
-(void) startScanning;
- (void)centralManagerDidUpdateState:(CBCentralManager *)central;
- (void)centralManager:(CBCentralManager *)central didRetrievePeripherals:(NSArray *)peripherals;
- (void)centralManager:(CBCentralManager *)central didRetrieveConnectedPeripherals:(NSArray *)peripherals;
- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI;
- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral;
- (void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;
- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;

- (void)peripheral:(CBPeripheral *)peripheral didDiscoverServices:(NSError *)error;
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError *)error;
- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;
- (void)peripheral:(CBPeripheral *)peripheral didUpdateNotificationStateForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;

-(void) shutDown;
@end
