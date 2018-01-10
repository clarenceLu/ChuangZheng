//
//  QRViewController.m
//  Chuangzheng-mobile
//
//  Created by lujiawei on 28/12/2017.
//

#import "QRViewController.h"
#import <AVFoundation/AVFoundation.h>
#import "QRCodeGenerateVC.h"
#import "SGQRCodeScanningVC.h"


@interface QRViewController ()

@end

@implementation QRViewController{
    
    UINavigationController *navVc;
    SGQRCodeScanningVC *vc;
    
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    
    //[self.view setBackgroundColor:[UIColor redColor]];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}




-(void)didSucessWithQR:(NSString*)QRStr{
    
    NSLog(@"%@",QRStr);
     
    [_delegate QRWithString:QRStr];
    
     [vc dismissViewControllerAnimated:YES completion:^(void){}];
    [self removeFromParentViewController];
}

-(NSString*)scanQRImage{

    AVCaptureDevice *device = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
    if (device) {
        AVAuthorizationStatus status = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
        if (status == AVAuthorizationStatusNotDetermined) {
            [AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo completionHandler:^(BOOL granted) {
                if (granted) {
                    dispatch_sync(dispatch_get_main_queue(), ^{
                        vc = [[SGQRCodeScanningVC alloc] init];
                        vc.delegate=self;
                       // [navVc pushViewController:vc animated:YES];
                          [self presentModalViewController:vc animated:YES];
                    });
                    // 用户第一次同意了访问相机权限
                    NSLog(@"用户第一次同意了访问相机权限 - - %@", [NSThread currentThread]);
                    
                } else {
                    // 用户第一次拒绝了访问相机权限
                    NSLog(@"用户第一次拒绝了访问相机权限 - - %@", [NSThread currentThread]);
                }
            }];
        } else if (status == AVAuthorizationStatusAuthorized) { // 用户允许当前应用访问相机
            vc = [[SGQRCodeScanningVC alloc] init];
             vc.delegate=self;
            //[navVc pushViewController:vc animated:YES];
            
              [self presentModalViewController:vc animated:YES];
        } else if (status == AVAuthorizationStatusDenied) { // 用户拒绝当前应用访问相机
            UIAlertController *alertC = [UIAlertController alertControllerWithTitle:@"温馨提示" message:@"请去-> [设置 - 隐私 - 相机 - SGQRCodeExample] 打开访问开关" preferredStyle:(UIAlertControllerStyleAlert)];
            UIAlertAction *alertA = [UIAlertAction actionWithTitle:@"确定" style:(UIAlertActionStyleDefault) handler:^(UIAlertAction * _Nonnull action) {
                
            }];
            
            [alertC addAction:alertA];
            [self presentViewController:alertC animated:YES completion:nil];
            
        } else if (status == AVAuthorizationStatusRestricted) {
            NSLog(@"因为系统原因, 无法访问相册");
        }
    } else {
        UIAlertController *alertC = [UIAlertController alertControllerWithTitle:@"温馨提示" message:@"未检测到您的摄像头" preferredStyle:(UIAlertControllerStyleAlert)];
        UIAlertAction *alertA = [UIAlertAction actionWithTitle:@"确定" style:(UIAlertActionStyleDefault) handler:^(UIAlertAction * _Nonnull action) {
            
        }];
        
        [alertC addAction:alertA];
        [self presentViewController:alertC animated:YES completion:nil];
    }

    
    
}


-(void)LocalPhoto{
    UIImagePickerController *picker = [[UIImagePickerController alloc] init];
    
    picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    picker.delegate = self;
    //设置选择后的图片可被编辑
    //picker.allowsEditing = YES;
    [self presentModalViewController:picker animated:YES];
}



-(void)takePhoto
{
    UIImagePickerControllerSourceType sourceType = UIImagePickerControllerSourceTypeCamera;
    if ([UIImagePickerController isSourceTypeAvailable: UIImagePickerControllerSourceTypeCamera])
    {
        UIImagePickerController *picker = [[UIImagePickerController alloc] init];
        picker.delegate = self;
        //设置拍照后的图片可被编辑
        //picker.allowsEditing = YES;
        picker.sourceType = sourceType;
        [self presentModalViewController:picker animated:YES];
    }else
    {
        NSLog(@"模拟其中无法打开照相机,请在真机中使用");
    }
}


-(UIImage*)set_imageWithImage:(UIImage*)myImage
                       ToPoint:(CGPoint)newPoint
                  scaledToSize:(CGSize)newSize

{
    UIGraphicsBeginImageContext(newSize);
    
    [myImage drawInRect:CGRectMake(newPoint.x,newPoint.y,newSize.width,newSize.height)];
    
    UIImage* newImage = UIGraphicsGetImageFromCurrentImageContext();
    
    UIGraphicsEndImageContext();
    
    return newImage;
}

-(NSData*)set_ImageData_UIImageJPEGRepresentationWithImage:(UIImage*)image
                                CGFloat_compressionQuality:(CGFloat)image_float
{
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    [formatter setTimeZone:[NSTimeZone systemTimeZone]];
    [formatter setDateFormat:@"yyyyMMddHHmmss"];
    NSString* dateString = [formatter stringFromDate:[NSDate date]];
    dateString = [NSString stringWithFormat:@"%@.png",dateString];
    NSData *imageData = UIImagePNGRepresentation(image);
    return imageData;
}




- (void) imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    NSString *type = [info objectForKey:UIImagePickerControllerMediaType];
    
    //当选择的类型是图片
    if ([type isEqualToString:@"public.image"])
    {
        //先把图片转成NSData
        UIImage* MyImage = [[UIImage alloc]init];
        
        UIImage* image = [info objectForKey:UIImagePickerControllerOriginalImage];
        NSData *imageData = UIImagePNGRepresentation(image);
        
        MyImage=[self set_imageWithImage:image ToPoint:CGPointMake(0, 0)  scaledToSize:CGSizeMake(image.size.width, image.size.height)];
        NSData * data = [self set_ImageData_UIImageJPEGRepresentationWithImage:MyImage CGFloat_compressionQuality:0.5];
        
        
        NSString * DocumentsPath = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents"];
        NSFileManager *fileManager = [NSFileManager defaultManager];
        [fileManager createDirectoryAtPath:DocumentsPath withIntermediateDirectories:YES attributes:nil error:nil];

        NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
        [formatter setTimeZone:[NSTimeZone systemTimeZone]];
        [formatter setDateFormat:@"yyyyMMddHHmmss"];
        NSString* dateString = [formatter stringFromDate:[NSDate date]];
        dateString = [NSString stringWithFormat:@"%@.png",dateString];
        NSString* filePath = [[NSString alloc]initWithFormat:@"%@/%@",DocumentsPath,dateString];
        [fileManager removeItemAtPath:filePath error:nil];

        [fileManager createFileAtPath:filePath contents:data attributes:nil];

        NSLog(@"%@",filePath);
        
       [picker dismissViewControllerAnimated:YES completion:^(void){}];
    
        if ([_delegate respondsToSelector:@selector(imageDelegateUrl:)]) {
            [_delegate imageDelegateUrl:filePath]; // 通知执行协议方法
        }
        
        [self removeFromParentViewController];
        
    }
}

@end
