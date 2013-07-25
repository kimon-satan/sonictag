/*
 This file is part of 'Sonic Tag'.
 This software is released under a simplified BSD license, modified for non-commercial use only.
 
 Copyright (c) 2013, M.Grierson, Embodied AudioVisual Interaction Group, Goldsmiths, University of London
 
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are
 met:
 
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above
 copyright notice, this list of conditions and the following disclaimer
 in the documentation and/or other materials provided with the
 distribution.
 * Any redistribution, use, or modification is done solely for
 personal benefit and not for any commercial purpose or for monetary
 gain
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 For further information:
 http://eavi.goldsmithsdigital.com/sound-image-and-brain/
 http://eavi.goldsmithsdigital.com/sonic-tag/
 
 */


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
}

- (void)centralManager:(CBCentralManager *)central didRetrievePeripherals:(NSArray *)peripherals {
    NSLog(@"Retrieved peripheral: %d - %@", [peripherals count], peripherals);
    [manager stopScan];
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
    
}
- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral {
    NSLog(@"did connect peripheral: %@ UUID: %@", peripheral, peripheral.UUID);
    CFStringRef cfuuid = CFUUIDCreateString(NULL, peripheral.UUID);
    [peripheral setDelegate:self];
    [peripheral discoverServices:nil];

}
- (void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error {
    NSLog(@"did fail to connect peripheral");
}
- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error
{
    NSLog(@"did disconnect peripheral");
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
