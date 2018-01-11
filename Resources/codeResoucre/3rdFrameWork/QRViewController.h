//
//  QRViewController.h
//  Chuangzheng-mobile
//
//  Created by lujiawei on 28/12/2017.
//

#import <UIKit/UIKit.h>



@protocol QRViewDelegate // 代理传值方法
-(void)imageDelegateUrl:(NSString*)ImageUrl;

-(void)QRWithString:(NSString*)QRStr;

@end


@interface QRViewController : UIViewController  <UINavigationControllerDelegate, UIImagePickerControllerDelegate>{
    
    
    
    
    
}
@property (weak, nonatomic) id delegate;

-(void)LocalPhoto;
-(void)takePhoto;

-(NSString*)scanQRImage;

@end
