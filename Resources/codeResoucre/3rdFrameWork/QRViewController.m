//
//  QRViewController.m
//  Chuangzheng-mobile
//
//  Created by lujiawei on 28/12/2017.
//

#import "QRViewController.h"


@interface QRViewController ()

@end

@implementation QRViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    
    //[self.view setBackgroundColor:[UIColor redColor]];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


-(NSString*)scanQRImage{
    
    
    
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
