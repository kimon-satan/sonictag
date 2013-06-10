//
//  BLEScanner.m
//  BLERx
//
//  Created by Chris Kiefer on 29/11/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#import "BLEScanner.h"

@implementation BLEScanner

@synthesize value;

- (id)init
{
    if ((self = [super init]))
    {
        //        self.characteristicsCBUUID = [NSMutableDictionary new];
        dicoveredPeripherals = [NSMutableArray new];
        manager = [[CBCentralManager alloc] initWithDelegate:self queue:nil];
    }
    return self;
}


-(void) startScanning {
    NSLog(@"Starting scan\n");
    NSDictionary *options = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithBool:FALSE], CBCentralManagerScanOptionAllowDuplicatesKey, nil];
    [manager scanForPeripheralsWithServices:dicoveredPeripherals options:options];
}

- (void)centralManagerDidUpdateState:(CBCentralManager *)central {
    //    if (![self supportLEHardware])
    //    {
    //        @throw ([NSError errorWithDomain:@"Bluetooth LE not supported"
    //                                    code:999
    //                                userInfo:nil]);
    //    }
}

- (void)centralManager:(CBCentralManager *)central didRetrievePeripherals:(NSArray *)peripherals {
    NSLog(@"Retrieved peripheral: %d - %@", [peripherals count], peripherals);
    [manager stopScan];
    //    for(int i=0; i < [peripherals count]; i++) {
    //        NSLog(@"Device: %@", [[peripherals objectAtIndex:i] UUIDString]);
    //        if ([[[peripherals objectAtIndex:i] UUIDString] isEqualToString:@"193E4B6F-A86A-7408-7159-9F27C38C4E6B"]) {
    //            testPeripheral = [peripherals objectAtIndex:i];
    //            [manager connectPeripheral:testPeripheral
    //                               options:[NSDictionary dictionaryWithObject:[NSNumber numberWithBool:YES] forKey:CBConnectPeripheralOptionNotifyOnDisconnectionKey]];
    //
    //        }
    //    }
    /* If there are any known devices, automatically connect to it.*/
    if([peripherals count] >= 1)
    {
        testPeripheral = [peripherals objectAtIndex:0];
        
        [manager connectPeripheral:testPeripheral
                           options:[NSDictionary dictionaryWithObject:[NSNumber numberWithBool:YES] forKey:CBConnectPeripheralOptionNotifyOnDisconnectionKey]];
    }
}

- (void)centralManager:(CBCentralManager *)central didRetrieveConnectedPeripherals:(NSArray *)peripherals {
    NSLog(@"did retrieve connected peripherals");
    
}
- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI {
    NSLog(@"Did discover peripheral. peripheral: %@ rssi: %@, UUID: %@ advertisementData: %@ ", peripheral, RSSI, peripheral.UUID, advertisementData);
    
    
    
    if(![dicoveredPeripherals containsObject:peripheral])
        [dicoveredPeripherals addObject:peripheral];

    [manager connectPeripheral:peripheral
                       options:[NSDictionary dictionaryWithObject:[NSNumber numberWithBool:YES] forKey:CBConnectPeripheralOptionNotifyOnDisconnectionKey]];
    
//    CFStringRef cfuuid = CFUUIDCreateString(NULL, peripheral.UUID);
//    CFComparisonResult res = CFStringCompare(cfuuid, CFSTR("193E4B6F-A86A-7408-7159-9F27C38C4E6B"), 0);
//    //    CFComparisonResult res = CFStringCompare(cfuuid, CFSTR("B5424021-9814-4C7B-E08B-8331383E4559"), 0);
//    
//    if (res == kCFCompareEqualTo) {
//        [manager retrievePeripherals:[NSArray arrayWithObject:(id)peripheral.UUID]];
//    }
    
}
- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral {
    NSLog(@"did connect peripheral: %@ UUID: %@", peripheral, peripheral.UUID);
    CFStringRef cfuuid = CFUUIDCreateString(NULL, peripheral.UUID);
//    CFComparisonResult res = CFStringCompare(cfuuid, CFSTR("C9935269-2DBE-0628-216C-25370A83D803"), 0);
//    CFComparisonResult res = CFStringCompare(cfuuid, CFSTR("5515C72B-2F36-6C60-93DA-9656EAF21879"), 0);
    
//    CFComparisonResult res = CFStringCompare(cfuuid, CFSTR("193E4B6F-A86A-7408-7159-9F27C38C4E6B"), 0);
    //CFComparisonResult res = CFStringCompare(cfuuid, CFSTR("BFBC6B57-451E-574A-3425-4337F50F5E75"), 0);
    CFComparisonResult res = CFStringCompare(cfuuid, CFSTR("D0EE567D-882B-BC22-5B76-9C211755F55E"), 0);
  

    if (res == kCFCompareEqualTo) {
        [peripheral setDelegate:self];
        [peripheral discoverServices:nil];
    }else{
        [manager cancelPeripheralConnection:peripheral];
    }

}
- (void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error {
    NSLog(@"did fail to connect peripheral");
}
- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error
{
    NSLog(@"did disconnect peripheral");
    //TODO: rescan
}


- (void)peripheral:(CBPeripheral *)peripheral didDiscoverServices:(NSError *)error {
    NSLog(@"Did discover services: %@\n\n%@", peripheral, peripheral.services);
    
    for(int i=0; i < peripheral.services.count; i++) {
        NSLog(@"UUID: %@", [[peripheral.services objectAtIndex:i] UUID]);
        [peripheral discoverCharacteristics:nil forService:[peripheral.services objectAtIndex:i]];
    }
}

- (void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError *)error {
    NSLog(@"Did discover characteristics: %@", service);
    for(int i=0; i < service.characteristics.count; i++) {
        NSLog(@"Characteristic: %@", [[service.characteristics objectAtIndex:i] UUID]);
        CBCharacteristic *ch = [service.characteristics objectAtIndex:i];
        NSData *data = ch.UUID.data;
        NSUInteger bytesToConvert = [data length];
        const unsigned char *uuidBytes = (const unsigned char*) [data bytes];
        NSMutableString *outputString = [NSMutableString stringWithCapacity:16];
        for (NSUInteger currentByteIndex = 0; currentByteIndex < bytesToConvert; currentByteIndex++)
        {
            switch (currentByteIndex)
            {
                case 3:
                case 5:
                case 7:
                case 9:[outputString appendFormat:@"%02x-", uuidBytes[currentByteIndex]]; break;
                default:[outputString appendFormat:@"%02x", uuidBytes[currentByteIndex]];
            }
            
        }
        NSLog(@"UUID: %@", outputString);
        //        if ([outputString isEqualToString:@"eb939815-1f64-4c21-85be-4c30e6c9da37"]) {
        if ([outputString isEqualToString:@"e7add780-b042-4876-aae1-112855353cc1"]) {
            //          if ([outputString isEqualToString:@"2a37"]) {
            NSLog(@"this one");
            [peripheral readValueForCharacteristic:ch];
            [peripheral setNotifyValue:YES forCharacteristic:ch];
        }
    }
}

- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error {
    //NSLog(@"new value: %@ %@", characteristic.UUID, characteristic.value);
    value = characteristic.value;
    [[NSNotificationCenter defaultCenter] postNotificationName:@"notify" object:self];
}

- (void)peripheral:(CBPeripheral *)peripheral didUpdateNotificationStateForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error {
    NSLog(@"did update notification for characteristic: %@ %@", characteristic.UUID, characteristic.value);
}

@end
