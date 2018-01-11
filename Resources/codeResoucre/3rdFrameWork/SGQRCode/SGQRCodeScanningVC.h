//
//  SGQRCodeScanningVC.h
//  SGQRCodeExample
//
//  Created by kingsic on 17/3/20.
//  Copyright © 2017年 kingsic. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol SGQRCodeViewDelegate // 代理传值方法


-(void)didSucessWithQR:(NSString*)QRStr;



@end





@interface SGQRCodeScanningVC : UIViewController
{
    
    
    
}

@property (weak, nonatomic) id delegate;

@end
