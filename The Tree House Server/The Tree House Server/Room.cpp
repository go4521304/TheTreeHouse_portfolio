#pragma once
#include "stdafx.h"
#include "Room.h"
#include "GameObject.h"
#include "Character.h"
#include "UserManager.h"
#include "User.h"

int cRoom::m_last_object_id = 0;



void cRoom::InitObjects()
{


}

void cRoom::StartGame()
{
	
	//월드 초기 설정


	//캐릭터 설정
	{
		cCharacter* character = cRoomManager::m_character_pool.PopObject();
		character->SetScale({ 100,100,100 });
		character->SetCharacterTransform({ -75000,19000,9200 }, { 0,0,0},
			{ 0,0,0 }, { 0,0,0 }, { 0, 0, 0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 });
		character->m_object_type = 100001;
		character->m_id = m_users[user_type::HOST]->GetID();
		m_users[user_type::HOST]->m_character = character;

		sc_put_object_packet packet;

		packet.size = sizeof(sc_put_object_packet);
		packet.type = SC_PACKET::SC_PUT_OBJECT;
		packet.object_type = character->m_object_type;
		packet.id = m_users[user_type::HOST]->GetID();

		Transform transform = character->GetTransform();
		packet.x = transform.position.x;
		packet.y = transform.position.y;
		packet.z = transform.position.z;
		packet.pitch = transform.rotation.pitch;
		packet.yaw = transform.rotation.yaw;
		packet.roll = transform.rotation.roll;
		packet.scale_x = transform.scale.x;
		packet.scale_y = transform.scale.y;
		packet.scale_z = transform.scale.z;

		Broadcast(sizeof(sc_put_object_packet), &packet);
	}

	{
		cCharacter* character = cRoomManager::m_character_pool.PopObject();
		character->SetScale({ 100,100,100 });
		//character->SetCharacterTransform({ 1712,21700,9200 }, { 0,0,-9000 },			{ 0,0,0 }, { 0,0,0 }, { 0, 0, 0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 });
		character->SetCharacterTransform({ -60000,19000,9200 }, { 0,-18000,0 },
			{ 0,0,0 }, { 0,0,0 }, { 0, 0, 0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 });
		character->m_object_type = 100002;
		character->m_id = m_users[user_type::GUEST]->GetID();
		m_users[user_type::GUEST]->m_character = character;

		sc_put_object_packet packet;

		packet.size = sizeof(sc_put_object_packet);
		packet.type = SC_PACKET::SC_PUT_OBJECT;
		packet.object_type = character->m_object_type;
		packet.id = m_users[user_type::GUEST]->GetID();

		Transform transform = character->GetTransform();
		packet.x = transform.position.x;
		packet.y = transform.position.y;
		packet.z = transform.position.z;
		packet.pitch = transform.rotation.pitch;
		packet.yaw = transform.rotation.yaw;
		packet.roll = transform.rotation.roll;
		packet.scale_x = transform.scale.x;
		packet.scale_y = transform.scale.y;
		packet.scale_z = transform.scale.z;

		Broadcast(sizeof(sc_put_object_packet), &packet);
	}


	//월드 오브젝트
	{
		cGameObject* game_object = cRoomManager::m_object_pool.PopObject();
		game_object->SetTransform({ { -233838,-133995,48376 }, { 0,0,0 }, {131,131,131} });
		game_object->m_object_type = 400002;
		game_object->m_id = MAX_USER + m_last_object_id++;
		game_object->m_mesh_id = 0;
		m_game_objects.insert(pair<unsigned int, cGameObject*>{game_object->m_id, game_object});
		sc_put_object_packet packet;

		packet.size = sizeof(sc_put_object_packet);
		packet.type = SC_PACKET::SC_PUT_OBJECT;
		packet.object_type = game_object->m_object_type;
		packet.id = game_object->m_id;

		Transform transform = game_object->GetTransform();
		packet.x = transform.position.x;
		packet.y = transform.position.y;
		packet.z = transform.position.z;
		packet.pitch = transform.rotation.pitch;
		packet.yaw = transform.rotation.yaw;
		packet.roll = transform.rotation.roll;
		packet.scale_x = transform.scale.x;
		packet.scale_y = transform.scale.y;
		packet.scale_z = transform.scale.z;

		Broadcast(sizeof(sc_put_object_packet), &packet);
	}

	m_state = room_state::INGAME;
	cout << "Room [ " << m_id << " ] Started Game\n";
}

void cRoom::UserLoadingComplete(const unsigned int _user_id)
{





}

void cRoom::SendOtherPlayerTransform(const unsigned int _user_id)
{
	if (m_state == room_state::INGAME)
	{
		//unsigned int target_user_id = -1;
		//if (_user_id == m_user_id[user_type::HOST])
		//	target_user_id = m_user_id[user_type::GUEST];
		//else
		//	target_user_id = m_user_id[user_type::HOST];

		//	/*cout << "send - user" << i << " position " << g_temp_position[i].x << "," << g_temp_position[i].y << ", " << g_temp_position[i].z
		//		<< " // rotation " << g_temp_rotation[i].x << "," << g_temp_rotation[i].y << ", " << g_temp_rotation[i].z << endl;*/

		//	sc_player_data_packet packet;

		//	packet.size = sizeof(sc_player_data_packet);
		//	packet.type = SC_PACKET::SC_PLAYER_DATA;
		//	packet.id = target_user_id;

		//	cCharacter* character = cUserManager::m_users[target_user_id]->m_character;

		//	packet.x = character->m_transform.position.x;
		//	packet.y = character->m_transform.position.y;
		//	packet.z = character->m_transform.position.z;
		//	packet.pitch = character->m_transform.rotation.pitch;
		//	packet.yaw = character->m_transform.rotation.yaw;
		//	packet.roll = character->m_transform.rotation.roll;

		//	packet.head_x = character->m_head_position.x;
		//	packet.head_y = character->m_head_position.y;
		//	packet.head_z = character->m_head_position.z;
		//	packet.head_pitch = character->m_head_rotation.pitch;
		//	packet.head_yaw = character->m_head_rotation.yaw;
		//	packet.head_roll = character->m_head_rotation.roll;

		//	packet.rh_x = character->m_rh_position.x;
		//	packet.rh_y = character->m_rh_position.y;
		//	packet.rh_z = character->m_rh_position.z;
		//	packet.rh_pitch = character->m_rh_rotation.pitch;
		//	packet.rh_yaw = character->m_rh_rotation.yaw;
		//	packet.rh_roll = character->m_rh_rotation.roll;

		//	packet.lh_x = character->m_lh_position.x;
		//	packet.lh_y = character->m_lh_position.y;
		//	packet.lh_z = character->m_lh_position.z;
		//	packet.lh_pitch = character->m_lh_rotation.pitch;
		//	packet.lh_yaw = character->m_lh_rotation.yaw;
		//	packet.lh_roll = character->m_lh_rotation.roll;

		//	cout << "SC_PLAYER_DATA to User [ " << _user_id << " ] In Room [ "<<(int)m_id<<" ] // User [ "<< target_user_id
		//		<<" ] position " << packet.x << "," << packet.y << ", " << packet.z
		//		<< " // rotation " << packet.pitch << ", " << packet.yaw << "," << packet.roll  << endl;
		//	
		//	cUserManager::m_users[_user_id]->Send(sizeof(packet), &packet);
	
	}
}

void cRoom::SendPlayerData()
{
	if (m_state == room_state::INGAME)
	{
		for (int i = 0; i < 2; ++i)
		{

			/*cout << "send - user" << i << " position " << g_temp_position[i].x << "," << g_temp_position[i].y << ", " << g_temp_position[i].z
				<< " // rotation " << g_temp_rotation[i].x << "," << g_temp_rotation[i].y << ", " << g_temp_rotation[i].z << endl;*/

			sc_player_data_packet packet;

			packet.size = sizeof(sc_player_data_packet);
			packet.type = SC_PACKET::SC_PLAYER_DATA;
			packet.id = m_users[1-i]->GetID();

			cCharacter* character = m_users[1 - i]->m_character;

			packet.x = character->m_transform.position.x;
			packet.y = character->m_transform.position.y;
			packet.z = character->m_transform.position.z;
			packet.pitch = character->m_transform.rotation.pitch;
			packet.yaw = character->m_transform.rotation.yaw;
			packet.roll = character->m_transform.rotation.roll;

			packet.head_x = character->m_head_position.x;
			packet.head_y = character->m_head_position.y;
			packet.head_z = character->m_head_position.z;
			packet.head_pitch = character->m_head_rotation.pitch;
			packet.head_yaw = character->m_head_rotation.yaw;
			packet.head_roll = character->m_head_rotation.roll;

			packet.rh_x = character->m_rh_position.x;
			packet.rh_y = character->m_rh_position.y;
			packet.rh_z = character->m_rh_position.z;
			packet.rh_pitch = character->m_rh_rotation.pitch;
			packet.rh_yaw = character->m_rh_rotation.yaw;
			packet.rh_roll = character->m_rh_rotation.roll;

			packet.lh_x = character->m_lh_position.x;
			packet.lh_y = character->m_lh_position.y;
			packet.lh_z = character->m_lh_position.z;
			packet.lh_pitch = character->m_lh_rotation.pitch;
			packet.lh_yaw = character->m_lh_rotation.yaw;
			packet.lh_roll = character->m_lh_rotation.roll;

			cout << "SC_PLAYER_DATA to User [ " << m_users[i]->GetID() << " ] In Room [ " << (int)m_id << " ] // User [ " << m_users[1 - i]->GetID()
				<< " ] position " << packet.x << "," << packet.y << ", " << packet.z
				<< " // rotation " << packet.pitch << ", " << packet.yaw << "," << packet.roll << endl;

			m_users[i]->Send(sizeof(packet), &packet);
		}
	}
}

void cRoom::SendAllObjectData()
{
	// 뷰리스트 등을 통한 최적화 필요
	for (const auto& p : m_game_objects)
	{
		sc_object_data_packet packet;

		packet.size = sizeof(sc_object_data_packet);
		packet.type = SC_PACKET::SC_OBJECT_DATA;
		packet.id = p.first;

		cGameObject* object = p.second;
		packet.x = object->m_transform.position.x;
		packet.y = object->m_transform.position.y;
		packet.z = object->m_transform.position.z;
		packet.pitch = object->m_transform.rotation.pitch;
		packet.yaw = object->m_transform.rotation.yaw;
		packet.roll = object->m_transform.rotation.roll;
		packet.scale_x = object->m_transform.position.x;
		packet.scale_y = object->m_transform.position.y;
		packet.scale_z = object->m_transform.position.z;

		Broadcast(sizeof(sc_object_data_packet), &packet);
	}

}

void cRoom::ShootBullet(cUser* _user, iVector3 _source_position, sRotation3 _rotation)
{
	sc_shoot_bullet_packet packet;
	packet.type = SC_PACKET::SC_SHOOT_BULLET;
	packet.size = sizeof(sc_shoot_bullet_packet);

	// HOST = 여자캐릭터, GUEST = 남자캐릭터 기준. 로비 제작 후 캐릭터 선택 가능하게 되면 수정 필요
	if (m_users[user_type::HOST] == _user)
		packet.bullet_type = 1;
	else
		packet.bullet_type = 2;

	packet.x = _source_position.x;
	packet.y = _source_position.y;
	packet.z = _source_position.z;
	packet.pitch = _rotation.pitch;
	packet.yaw = _rotation.yaw;
	packet.roll = _rotation.roll;

	Broadcast(sizeof(sc_shoot_bullet_packet), &packet);
}
void cRoom::Broadcast(int _size, void* _mess)
{
	m_users[0]->Send(_size, _mess);
	m_users[1]->Send(_size, _mess);
}

